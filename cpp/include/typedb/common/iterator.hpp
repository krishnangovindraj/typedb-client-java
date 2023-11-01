


#pragma once

#include <iterator>

#include "typedb/common/native.hpp"

namespace TypeDB {

template <
    typename NATIVE_ITER, typename NATIVE_T, typename T
>
class TypeDBIterator : public std::iterator<std::input_iterator_tag, T> {
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

    static SELF end;

    TypeDBIterator(NATIVE_ITER* nativeIterator) {
        iteratorNative = NativePointer<NATIVE_ITER>(nativeIterator, fn_nativeIterDrop);
        pNext = NativePointer<NATIVE_T>(nullptr);
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

    // bool operator==(SELF other) {
    //     return iteratorNative == other.iteratorNative;
    // }

    // bool operator!=(SELF other) {
    //     return !(*this == other);
    // }
    
    // SELF operator++(int) = delete;

    // SELF& operator++() {
    //     next();
    // }

    // T& operator*() const { 
    //     if (pNext == nullptr) {
    //         throw TypeDBDriverException("[TYPEDB_DRIVER_INTERNAL]", "Attempted to dereference an iterator which was uninitialised OR ")
    //     }
    //     return ;
    // }

};

// template < typename NATIVE_ITER, typename NATIVE_T, typename T > 
// std::function<void(NATIVE_ITER*)> TypeDBIterator<NATIVE_ITER, NATIVE_T, T>::*fn_nativeIterDrop;

// template < typename NATIVE_ITER, typename NATIVE_T, typename T > 
// std::function<NATIVE_T*(NATIVE_ITER*)> TypeDBIterator<NATIVE_ITER, NATIVE_T, T>::*fn_nativeIterNext;

// template < typename NATIVE_ITER, typename NATIVE_T, typename T > 
//     std::function<void(NATIVE_T*)> TypeDBIterator<NATIVE_ITER, NATIVE_T, T>::*fn_nativeElementDrop;

}
