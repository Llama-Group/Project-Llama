//
//  LLObject.h
//  LLObject
//
//  Created by BlueCocoa on 2016/8/15.
//  Copyright © 2016 BlueCocoa. All rights reserved.
//

#ifndef LLAMA_CPP_SRC_DATASTRUCTURE_LLOBJECT_H_
#define LLAMA_CPP_SRC_DATASTRUCTURE_LLOBJECT_H_

#include <Utility/Functor.h>
#include <utility>

namespace llama {
template<class T>
using StorageType = typename std::decay<T>::type;

template <typename R = void>
class LLObjectWrapper {
 public:
    /**
     *  @brief Default constructor
     */
    LLObjectWrapper() noexcept : ptr(nullptr) {
    }

    /**
     *  @brief Constructor for basic types
     */
    template <typename T>
    explicit LLObjectWrapper(T&& value) : ptr(new Derived<StorageType<T>>(std::forward<T>(value))) {
    }

    /**
     *  @brief Copy constructor for lvalue
     */
    explicit LLObjectWrapper(LLObjectWrapper * that) {
        ptr = that->clone();
        _is_function = that->_is_function;
    }

    /**
     *  @brief Copy constructor for rvalue
     */
    LLObjectWrapper(LLObjectWrapper&& that) {
        ptr = that.clone();
        _is_function = that._is_function;
        that.ptr = nullptr;
    }

    /**
     *  @brief Copy constructor for const lvalue
     */
    LLObjectWrapper(const LLObjectWrapper& that) {
        ptr = that.clone();
        _is_function = that._is_function;
    }

    /**
     *  @brief Copy constructor for const rvalue
     */
    LLObjectWrapper(const LLObjectWrapper&& that) {
        ptr = that.clone();
        _is_function = that._is_function;
    }

    /**
     *  @brief Copy constructor for lvalue of Functor
     */
    explicit LLObjectWrapper(FunctorWrapper<R> * function) {
        ptr = static_cast<Base *>(
                static_cast<void *>(
                  new std::function<void()>(
                    *static_cast<std::function<void()>*>(function->_function))));
        _is_function = true;
    }

    /**
     *  @brief Copy constructor for rvalue of Functor
     */
    explicit LLObjectWrapper(FunctorWrapper<R>&& function) {
        ptr = static_cast<Base *>(
                static_cast<void *>(
                  new std::function<void()>(
                    *static_cast<std::function<void()>*>(function._function))));
        _is_function = true;
    }

    /**
     *  @brief Copy constructor for const lvalue of Functor
     */
    explicit LLObjectWrapper(const FunctorWrapper<R>& function) {
        ptr = static_cast<Base *>(
                static_cast<void *>(
                  new std::function<void()>(
                    *static_cast<std::function<void()>*>(function._function))));
        _is_function = true;
    }

    /**
     *  @brief Copy constructor for const rvalue of Functor
     */
    explicit LLObjectWrapper(const FunctorWrapper<R>&& function) {
        ptr = static_cast<Base *>(
                static_cast<void *>(
                  new std::function<void()>(
                    *static_cast<std::function<void()>*>(function._function))));
        _is_function = true;
    }

    /**
     *  @brief Deconstructor
     */
    ~LLObjectWrapper() {
        if (ptr) {
            delete ptr;
        }
    }

    /**
     *  @brief Assignment copy lvalue
     */
    LLObjectWrapper& operator=(const LLObjectWrapper& object) {
        if (ptr != object.ptr) {
            auto old_ptr = ptr;
            ptr = object.clone();
            if (old_ptr && !object._is_function) {
                delete old_ptr;
            }
        }
        return *this;
    }

    /**
     *  @brief Assignment copy rvalue
     */
    LLObjectWrapper& operator=(LLObjectWrapper&& object) {
        if (ptr != object.ptr) {
            std::swap(ptr, object.ptr);
        }
        return *this;
    }

    /**
     *  @brief Assignment copy lvalue of Functor
     */
    LLObjectWrapper& operator=(const FunctorWrapper<R>& object) {
        auto old_ptr = ptr;
        ptr = static_cast<Base *>(
                static_cast<void *>(
                  new std::function<void()>(
                    *static_cast<std::function<void()>*>(object._function))));
        _is_function = true;
        if (old_ptr) {
            delete old_ptr;
        }
        return *this;
    }

    /**
     *  @brief Assignment copy rvalue of Functor
     */
    LLObjectWrapper& operator=(FunctorWrapper<R>&& object) {
        auto old_ptr = ptr;
        ptr = static_cast<Base *>(
                static_cast<void *>(
                  new std::function<void()>(
                    *static_cast<std::function<void()>*>(object._function))));
        _is_function = true;
        if (old_ptr) {
            delete old_ptr;
        }
        return *this;
    }

    /**
     *  @brief is class
     */
    template <typename T>
    bool is() const {
        auto derived = dynamic_cast<Derived<StorageType<T>>*>(ptr);
        return derived;
    }

    /**
     *  @brief explicit cast
     */
    template <typename T>
    StorageType<T>& cast() const {
        auto derived = dynamic_cast<Derived<StorageType<T>>*>(ptr);
        if (!derived) {
            throw std::bad_cast();
        } else {
            return derived->value;
        }
    }

    /**
     *  @brief implicit cast
     */
    template<class T>
    operator T() {
        return cast<StorageType<T>>();
    }

    /**
     *  @brief Return value as
     */
    template <typename AS>
    FunctorWrapper<AS> as() {
        // cast _functor.function to std::function
        auto function = static_cast<std::function<AS()>*>(static_cast<void *>(ptr));
        return FunctorWrapper<AS>(*function);
    }

    /**
     *  @brief Function call opreator
     *
     *  @param args Any parameters your function accecpts
     */
    template <typename ... Args>
    R operator() (Args&& ... args) {
        // cast _functor.function to std::function
        auto function = static_cast<std::function<R(Args ...)>*>(static_cast<void *>(ptr));

        // call it
        if (!std::is_same<R, void>::value) {
            return (*function)(std::forward<Args>(args)...);
        }
        (*function)(std::forward<Args>(args)...);
    }

 private:
    struct Base {
        virtual ~Base() {
        }

        virtual Base * clone() const = 0;
    };

    template <typename T>
    struct Derived : Base {
        template <typename U>
        explicit Derived(U&& value) : value(std::forward<U>(value)) {
        }

        T value;

        Base * clone() const {
            return new Derived<T>(value);
        }
    };

    Base * clone() const {
        if (ptr) {
            return ptr->clone();
        } else {
            return nullptr;
        }
    }

    Base * ptr;
    bool _is_function;
};

using LLObject = LLObjectWrapper<>;
}  // namespace llama

#endif  // LLAMA_CPP_SRC_DATASTRUCTURE_LLOBJECT_H_
