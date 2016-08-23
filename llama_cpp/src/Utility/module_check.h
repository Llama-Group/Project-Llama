//
//  module_check.h
//  Project-LLama
//
//  Created by BlueCocoa on 2016/8/16.
//  Copyright © 2016 BlueCocoa. All rights reserved.
//

#ifndef LLAMA_CPP_SRC_UTILITY_MODULE_CHECK_H_
#define LLAMA_CPP_SRC_UTILITY_MODULE_CHECK_H_

/**
 *  @brief Define a function to check whether a given class can perform a specific method or not
 *
 *  @discussion
 *         For instance, we have such classes

 *          class A {
 *           public:
 *              void method_1();
 *          };
 *          class B {
 *           public:
 *              void method_2(int);
 *          };
 *
 *         To check whether they can perform method or not, we can write
 *
 *          module_check(perform_method_1, method)
 *          module_check(perform_method_2, method, int)
 *
 *         The extra int behind 'method,' is the type of that method
 *
 *         Then two structs named module_check_perform_method_1 and module_check_perform_method_2 will be generated
 *         To use they
 *
 *          if (module_check_perform_method_1<A, void>::value) {
 *              // true
 *          }
 *          if (module_check_perform_method_1<A, int>::value) {
 *              // false due to return type does not match
 *          }
 *          if (module_check_perform_method_1<B, void>::value) {
 *              // false due to arg type does not match
 *          }
 *
 *          if (module_check_perform_method_2<B, void>::value) {
 *              // true
 *          }
 *          if (module_check_perform_method_2<B, int>::value) {
 *              // false due to return type does not match
 *          }
 *          if (module_check_perform_method_2<A, void>::value) {
 *              // false due to arg type does not match
 *          }
 *
 *         Or
 *
 *          class SmartClass {
 *           public:
 *              template <typename T, typename = typename std::enable_if<module_check_perform_method_2<T, void>::value, int>::type>
 *              SmartClass(const T& object_with_arg_type_int) {
 *                  object_with_arg_type_int.method_1(233);
 *              }
 *          };
 *
 *          //  A a;
 *          //  SmartClass smart1(a); // this line won't compile
 *
 *          B b;
 *          SmartClass smart2(b);
 *
 *  @note  This only applies to public method
 */

#define module_check(module_name, method_name, ...)\
template <typename T, typename R>\
struct module_check_##module_name {\
    typedef char (&no)  [1];\
    typedef char (&yes) [2];\
    template <typename U, R (T::*)(__VA_ARGS__)>\
    struct function_match;\
    template <typename U, R (T::*)(__VA_ARGS__) const>\
    struct function_match_const;\
    template <typename U>\
    static yes check(function_match<U, &U::method_name>*);\
    template <typename U>\
    static yes check(function_match_const<U, &U::method_name>*);\
    template <typename U>\
    static no check(...);\
    enum {\
        value = (sizeof(check<T>(0)) == sizeof(yes))\
    };\
};

/**
 *  @brief  A variant of module_check
 *
 *  @discussion Define a function to check whether a given class can perform a specific method (only with const qualified) or not
 */
#define module_check_const(module_name, method_name, ...)\
template <typename T, typename R>\
struct module_check_##module_name {\
    typedef char (&no)  [1];\
    typedef char (&yes) [2];\
    template <typename U, R (T::*)(__VA_ARGS__) const>\
    struct function_match_const;\
    template <typename U>\
    static yes check(function_match_const<U, &U::method_name>*);\
    template <typename U>\
    static no check(...);\
    enum {\
        value = (sizeof(check<T>(0)) == sizeof(yes))\
    };\
};

/**
 *  @brief Define a function to check whether a given class can perform a specific method or not
 *
 *  @discussion
 *         This macro acts pretty much like the one above, the only difference is that this accepts arg type in code
 *         For instance,

 *          class A {
 *           public:
 *              void method_1(double);
 *          };
 *          class B {
 *           public:
 *              void method_1(int);
 *          };
 *
 *         And we write
 *
 *          module_check_t(perform_method_1, method)
 *
 *         Then a struct named module_check_perform_method_1 will be generated
 *         To use it
 *
 *          if (module_check_perform_method_1<A, void, double>::value) {
 *              // true
 *          }
 *          if (module_check_perform_method_1<A, void>::value) {
 *              // false due to arg type does not match
 *          }
 *          if (module_check_perform_method_1<B, void, int>::value) {
 *              // true
 *          }
 *          if (module_check_perform_method_1<B, void>::value) {
 *              // false due to arg type does not match
 *          }
 *
 *         Or
 *
 *          class SmartClass {
 *           public:
 *              template <typename T, typename = typename std::enable_if<module_check_perform_method_1<T, void, double>::value, int>::type>
 *              SmartClass(const T& object_with_method_1_arg_type_double) {
 *                  object_with_method_1_arg_type_double.method_1(2.33);
 *              }
 *          };
 *
 *          A a;
 *          SmartClass smart1(a);
 *
 *          //    B b;
 *          //    SmartClass smart2(b); // this line won't compile
 *
 *  @note  This only applies to public method
 */
#define module_check_t(module_name, method_name)\
template <typename T, typename R, typename ... Args>\
struct module_check_##module_name {\
    typedef char (&no)  [1];\
    typedef char (&yes) [2];\
    template <typename U, R (T::*)(Args ...)>\
    struct function_match;\
    template <typename U, R (T::*)(Args ...) const>\
    struct function_match_const;\
    template <typename U>\
    static yes check(function_match<U, &U::method_name>*);\
    template <typename U>\
    static yes check(function_match_const<U, &U::method_name>*);\
    template <typename U>\
    static no check(...);\
    enum {\
        value = (sizeof(check<T>(0)) == sizeof(yes))\
    };\
};

/**
 *  @brief  A variant of module_check_t
 *
 *  @discussion Define a function to check whether a given class can perform a specific method (only with const qualified) or not
 */
#define module_check_const_t(module_name, method_name)\
template <typename T, typename R, typename ... Args>\
struct module_check_##module_name {\
    typedef char (&no)  [1];\
    typedef char (&yes) [2];\
    template <typename U, R (T::*)(Args ...) const>\
    struct function_match_const;\
    template <typename U>\
    static yes check(function_match_const<U, &U::method_name>*);\
    template <typename U>\
    static no check(...);\
    enum {\
        value = (sizeof(check<T>(0)) == sizeof(yes))\
    };\
};

#endif  // LLAMA_CPP_SRC_UTILITY_MODULE_CHECK_H_
