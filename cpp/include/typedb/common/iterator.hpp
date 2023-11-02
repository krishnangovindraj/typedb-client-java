

#pragma once

#include <iterator>

#include "typedb/common/native.hpp"
#include "typedb/common/TypeDBDriverException.hpp"

namespace TypeDB {

template <
    typename NATIVE_ITER,
    typename NATIVE_T,
    typename T>
class TypeDBIterator {
    // Start with the java style iterator. Can implement std::iterator style functions later.

    using SELF = TypeDBIterator<NATIVE_ITER, NATIVE_T, T>;

   private:
    NativePointer<NATIVE_ITER> iteratorNative;
    NativePointer<NATIVE_T> pNext;

   protected:
    static std::function<void(NATIVE_ITER*)> fn_nativeIterDrop;
    static std::function<NATIVE_T*(NATIVE_ITER*)> fn_nativeIterNext;
    static std::function<void(NATIVE_T*)> fn_nativeElementDrop;

   public:

    
    TypeDBIterator(NATIVE_ITER* nativeIterator) {
        iteratorNative = NativePointer<NATIVE_ITER>(nativeIterator, fn_nativeIterDrop);
        pNext = NativePointer<NATIVE_T>(nullptr);
    }

    TypeDBIterator(SELF& other) = delete;

    TypeDBIterator(SELF&& from) {
        *this = std::move(from);
    }

    SELF& operator=(SELF&& from) {
        iteratorNative = std::move(from.iteratorNative);
        pNext = std::move(from.pNext);
        return *this;
    }

    bool hasNext() {
        if (pNext.get() == nullptr && iteratorNative != nullptr) {
            _native::Database* p = fn_nativeIterNext(iteratorNative.get());
            if (p != nullptr) {
                pNext = NativePointer<NATIVE_T>(p, fn_nativeElementDrop);
            } else {
                // We're at the end of the iterator
                pNext = NativePointer<NATIVE_T>(nullptr);
                iteratorNative.reset();
            }
        }
        return pNext.get() != nullptr;
    }

    T next() {
        if (hasNext()) {
            return T(pNext.release());
        } else {
            throw std::out_of_range("next() was called on iterator which does not have a next element.");
        }
    }
};

// TODO: Improve or combine into one.
template <
    typename NATIVE_ITER,
    typename NATIVE_T,
    typename T>
class IteratorWrapper : public std::iterator<std::input_iterator_tag, T> {

    using SELF = IteratorWrapper<NATIVE_ITER, NATIVE_T, T>;

   private:
    TypeDBIterator<NATIVE_ITER, NATIVE_T, T> wrappedIter;
    T obj;

    IteratorWrapper() : wrappedIter(nullptr), obj(nullptr) { }

   public:
    static SELF end;

    IteratorWrapper(TypeDBIterator<NATIVE_ITER, NATIVE_T, T>&& wrappedIter)
        : wrappedIter(std::move(wrappedIter)),
          obj(wrappedIter.hasNext() ? wrappedIter.next() : nullptr) {}

    IteratorWrapper(SELF& other) = delete;
    IteratorWrapper(SELF&& other) = delete;

    bool operator==(const SELF& other) {
        return wrappedIter.iteratorNative == other.wrappedIter.iteratorNative && obj == other.obj;
    }

    bool operator!=(const SELF& other) {
        return !(*this == other);
    }

    SELF operator++(int) = delete;  // Just use ++it.

    SELF& operator++() {
        if (wrappedIter.hasNext()) {
            obj = std::move(wrappedIter.next());
        } else {
            obj = std::move(T(nullptr));
        }
    }

    T& operator*() const {
        if (obj == end) {
            throw TypeDBDriverCustomException("[CUSTOM]", "Dereferenced iterator");
        }
        return obj;
    }
};

template <
    typename NATIVE_ITER,
    typename NATIVE_T,
    typename T
> IteratorWrapper<NATIVE_ITER, NATIVE_T, T> IteratorWrapper<NATIVE_ITER, NATIVE_T, T>::end = IteratorWrapper();

}  // namespace TypeDB
