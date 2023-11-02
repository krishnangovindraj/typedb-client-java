

#pragma once

#include <iostream>

#include <iterator>

#include "typedb/common/native.hpp"
#include "typedb/common/TypeDBDriverException.hpp"

namespace TypeDB {
template <
    typename NATIVE_ITER,
    typename NATIVE_T,
    typename T>
class BaseIterable;

template <
    typename NATIVE_ITER,
    typename NATIVE_T,
    typename T>
class BaseIterator : public std::iterator<std::input_iterator_tag, T> {

    using SELF = BaseIterator<NATIVE_ITER, NATIVE_T, T>;

   protected:

    // TODO: Make const & maybe public
    static std::function<void(NATIVE_ITER*)> fn_nativeIterDrop;
    static std::function<NATIVE_T*(NATIVE_ITER*)> fn_nativeIterNext;
    static std::function<void(NATIVE_T*)> fn_nativeElementDrop;

   private:
    
    NativePointer<NATIVE_ITER> iteratorNative;
    T obj;

    BaseIterator() : iteratorNative(nullptr), obj(nullptr) { }

    BaseIterator(SELF&& from) : iteratorNative(std::move(from.iteratorNative)), obj(std::move(from.obj)) { }

   public:
    static SELF end;
        
    BaseIterator(NATIVE_ITER* iteratorNative)
     : iteratorNative(iteratorNative, fn_nativeIterDrop),
       obj(nullptr) 
       { }

    BaseIterator(const SELF& from) = delete;


    SELF& operator=(const SELF& from) = delete;

    SELF& operator=(SELF&& from){
        iteratorNative = std::move(from.iteratorNative);
        obj = std::move(from.obj);
        return *this;
    }

    bool operator==(const SELF& other) {
        return iteratorNative == other.iteratorNative;
    }

    bool operator!=(const SELF& other) {
        return !(*this == other);
    }

    SELF operator++(int) = delete;  // Just use ++it.

    SELF& operator++() {
        NATIVE_T* p = fn_nativeIterNext(iteratorNative.get());
        obj = std::move(T(p));
        if (p == nullptr) {
            iteratorNative.reset(); // Makes it equal to end.
        }
        return *this;
    }

    T& operator*() {
        if ((*this) == end) {
            throw TypeDBDriverCustomException("[CUSTOM]", "Dereferenced iterator which has reached end (or was invalidated by a move).");
        }
        return obj;
    }

    friend class BaseIterable<NATIVE_ITER, NATIVE_T, T>;
};


// TODO: Improve or combine into one.
template <
    typename NATIVE_ITER,
    typename NATIVE_T,
    typename T>
class BaseIterable {

    using SELF = BaseIterable<NATIVE_ITER, NATIVE_T, T>;
    using ITERATOR = BaseIterator<NATIVE_ITER, NATIVE_T, T>;

   private:
    NativePointer<NATIVE_ITER> iteratorNative;

   public:
    BaseIterable(NATIVE_ITER* iteratorNative) : iteratorNative(iteratorNative, ITERATOR::fn_nativeIterDrop) { } 
    BaseIterable(SELF& from) = delete;
    BaseIterable(SELF&& from) {
        *this = std::move(from);
    }

    BaseIterable& operator=(const SELF& from) = delete; 
    
    BaseIterable& operator=(SELF&& from){
        iteratorNative = std::move(from.iteratorNative);
        return *this;
    }

    ITERATOR begin() {
        ITERATOR it = ITERATOR(iteratorNative.release());
        ++it; // initialises it
        return std::move(it);
    }

    const ITERATOR& end() {
        return ITERATOR::end;
    }
};

template <
    typename NATIVE_ITER,
    typename NATIVE_T,
    typename T
> BaseIterator<NATIVE_ITER, NATIVE_T, T> BaseIterator<NATIVE_ITER, NATIVE_T, T>::end = BaseIterator();




// template <
//     typename NATIVE_ITER,
//     typename NATIVE_T,
//     typename T>
// class TypeDBIterator {
//     // Start with the java style iterator. Can implement std::iterator style functions later.

//     using SELF = TypeDBIterator<NATIVE_ITER, NATIVE_T, T>;

//    private:
//     NativePointer<NATIVE_ITER> iteratorNative;
//     NativePointer<NATIVE_T> pNext;

//    protected:
//     static std::function<void(NATIVE_ITER*)> fn_nativeIterDrop;
//     static std::function<NATIVE_T*(NATIVE_ITER*)> fn_nativeIterNext;
//     static std::function<void(NATIVE_T*)> fn_nativeElementDrop;

//    public:

    
//     TypeDBIterator(NATIVE_ITER* nativeIterator) {
//         iteratorNative = NativePointer<NATIVE_ITER>(nativeIterator, fn_nativeIterDrop);
//         pNext = NativePointer<NATIVE_T>(nullptr);
//     }

//     TypeDBIterator(SELF& other) = delete;

//     TypeDBIterator(SELF&& from) {
//         *this = std::move(from);
//     }

//     SELF& operator=(SELF&& from) {
//         iteratorNative = std::move(from.iteratorNative);
//         pNext = std::move(from.pNext);
//         return *this;
//     }

//     bool hasNext() {
//         if (pNext.get() == nullptr && iteratorNative != nullptr) {
//             _native::Database* p = fn_nativeIterNext(iteratorNative.get());
//             if (p != nullptr) {
//                 pNext = NativePointer<NATIVE_T>(p, fn_nativeElementDrop);
//             } else {
//                 // We're at the end of the iterator
//                 pNext = NativePointer<NATIVE_T>(nullptr);
//                 iteratorNative.reset();
//             }
//         }
//         return pNext.get() != nullptr;
//     }

//     T next() {
//         if (hasNext()) {
//             return T(pNext.release());
//         } else {
//             throw std::out_of_range("next() was called on iterator which does not have a next element.");
//         }
//     }
// };

}  // namespace TypeDB
