#ifndef FOR_EACH_H
#define FOR_EACH_H

/* Make a FOREACH macro */
#define FE_1(WHAT, X) WHAT(X)
#define FE_2(WHAT, X, ...) WHAT(X)FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X)FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X)FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X)FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X)FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X)FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT(X)FE_7(WHAT, __VA_ARGS__)
#define FE_9(WHAT, X, ...) WHAT(X)FE_8(WHAT, __VA_ARGS__)
#define FE_10(WHAT, X, ...) WHAT(X)FE_9(WHAT, __VA_ARGS__)
#define FE_11(WHAT, X, ...) WHAT(X)FE_10(WHAT, __VA_ARGS__)
#define FE_12(WHAT, X, ...) WHAT(X)FE_11(WHAT, __VA_ARGS__)
#define FE_13(WHAT, X, ...) WHAT(X)FE_12(WHAT, __VA_ARGS__)
#define FE_14(WHAT, X, ...) WHAT(X)FE_13(WHAT, __VA_ARGS__)
#define FE_15(WHAT, X, ...) WHAT(X)FE_14(WHAT, __VA_ARGS__)
#define FE_16(WHAT, X, ...) WHAT(X)FE_15(WHAT, __VA_ARGS__)
#define FE_17(WHAT, X, ...) WHAT(X)FE_16(WHAT, __VA_ARGS__)
#define FE_18(WHAT, X, ...) WHAT(X)FE_17(WHAT, __VA_ARGS__)
#define FE_19(WHAT, X, ...) WHAT(X)FE_18(WHAT, __VA_ARGS__)
#define FE_20(WHAT, X, ...) WHAT(X)FE_19(WHAT, __VA_ARGS__)
#define FE_21(WHAT, X, ...) WHAT(X)FE_20(WHAT, __VA_ARGS__)
#define FE_22(WHAT, X, ...) WHAT(X)FE_21(WHAT, __VA_ARGS__)
#define FE_23(WHAT, X, ...) WHAT(X)FE_22(WHAT, __VA_ARGS__)
#define FE_24(WHAT, X, ...) WHAT(X)FE_23(WHAT, __VA_ARGS__)
#define FE_25(WHAT, X, ...) WHAT(X)FE_24(WHAT, __VA_ARGS__)
#define FE_26(WHAT, X, ...) WHAT(X)FE_25(WHAT, __VA_ARGS__)
#define FE_27(WHAT, X, ...) WHAT(X)FE_26(WHAT, __VA_ARGS__)
#define FE_28(WHAT, X, ...) WHAT(X)FE_27(WHAT, __VA_ARGS__)
#define FE_29(WHAT, X, ...) WHAT(X)FE_28(WHAT, __VA_ARGS__)
#define FE_30(WHAT, X, ...) WHAT(X)FE_29(WHAT, __VA_ARGS__)
#define FE_31(WHAT, X, ...) WHAT(X)FE_30(WHAT, __VA_ARGS__)
#define FE_32(WHAT, X, ...) WHAT(X)FE_31(WHAT, __VA_ARGS__)
#define FE_33(WHAT, X, ...) WHAT(X)FE_32(WHAT, __VA_ARGS__)
#define FE_34(WHAT, X, ...) WHAT(X)FE_33(WHAT, __VA_ARGS__)
#define FE_35(WHAT, X, ...) WHAT(X)FE_34(WHAT, __VA_ARGS__)
#define FE_36(WHAT, X, ...) WHAT(X)FE_35(WHAT, __VA_ARGS__)
#define FE_37(WHAT, X, ...) WHAT(X)FE_36(WHAT, __VA_ARGS__)
#define FE_38(WHAT, X, ...) WHAT(X)FE_37(WHAT, __VA_ARGS__)
#define FE_39(WHAT, X, ...) WHAT(X)FE_38(WHAT, __VA_ARGS__)
#define FE_40(WHAT, X, ...) WHAT(X)FE_39(WHAT, __VA_ARGS__)
#define FE_41(WHAT, X, ...) WHAT(X)FE_40(WHAT, __VA_ARGS__)
#define FE_42(WHAT, X, ...) WHAT(X)FE_41(WHAT, __VA_ARGS__)
#define FE_43(WHAT, X, ...) WHAT(X)FE_42(WHAT, __VA_ARGS__)
#define FE_44(WHAT, X, ...) WHAT(X)FE_43(WHAT, __VA_ARGS__)
#define FE_45(WHAT, X, ...) WHAT(X)FE_44(WHAT, __VA_ARGS__)
#define FE_46(WHAT, X, ...) WHAT(X)FE_45(WHAT, __VA_ARGS__)
#define FE_47(WHAT, X, ...) WHAT(X)FE_46(WHAT, __VA_ARGS__)
#define FE_48(WHAT, X, ...) WHAT(X)FE_47(WHAT, __VA_ARGS__)
#define FE_49(WHAT, X, ...) WHAT(X)FE_48(WHAT, __VA_ARGS__)

#define GET_MACRO(\
        _1, _2, _3, _4, _5, \
        _6, _7, _8, _9, _10,\
        _11, _12, _13, _14, _15, \
        _16, _17, _18, _19, _20, \
        _21, _22, _23, _24, _25, \
        _26, _27, _28, _29, _30, \
        _31, _32, _33, _34, _35, \
        _36, _37, _38, _39, _40, \
        _41, _42, _43, _44, _45, \
        _46, _47, _48, _49, _50, \
        _51, _52, _53, _54, _55, \
        _56, _57, _58, _59, NAME, ...) NAME
#define FOR_EACH(action, ...) \
    GET_MACRO(__VA_ARGS__, FE_59, FE_58, FE_57, FE_56, \
            FE_55, FE_54, FE_53, FE_52, FE_51, \
            FE_50, FE_49, FE_48, FE_47, FE_46, \
            FE_45, FE_44, FE_43, FE_42, FE_41, \
            FE_40, FE_39, FE_38, FE_37, FE_36, \
            FE_35, FE_34, FE_33, FE_32, FE_31, \
            FE_30, FE_29, FE_28, FE_27, FE_26, \
            FE_25, FE_24, FE_23, FE_22, FE_21, \
            FE_20, FE_19, FE_18, FE_17, FE_16, \
            FE_15, FE_14, FE_13, FE_12, FE_11, \
            FE_10, FE_9, FE_8, FE_7, FE_6, \
            FE_5, FE_4, FE_3, FE_2, FE_1)(action, __VA_ARGS__)

#define FE_2_1(WHAT, X, Y) WHAT(X, Y)
#define FE_2_2(WHAT, X, Y, ...) WHAT(X, Y)FE_2_1(WHAT, X, __VA_ARGS__)
#define FE_2_3(WHAT, X, Y, ...) WHAT(X, Y)FE_2_2(WHAT, X, __VA_ARGS__)
#define FE_2_4(WHAT, X, Y, ...) WHAT(X, Y)FE_2_3(WHAT, X, __VA_ARGS__)
#define FE_2_5(WHAT, X, Y, ...) WHAT(X, Y)FE_2_4(WHAT, X, __VA_ARGS__)
#define FE_2_6(WHAT, X, Y, ...) WHAT(X, Y)FE_2_5(WHAT, X, __VA_ARGS__)
#define FE_2_7(WHAT, X, Y, ...) WHAT(X, Y)FE_2_6(WHAT, X, __VA_ARGS__)
#define FE_2_8(WHAT, X, Y, ...) WHAT(X, Y)FE_2_7(WHAT, X, __VA_ARGS__)
#define FE_2_9(WHAT, X, Y, ...) WHAT(X, Y)FE_2_8(WHAT, X, __VA_ARGS__)
#define FE_2_10(WHAT, X, Y, ...) WHAT(X, Y)FE_2_9(WHAT, X, __VA_ARGS__)
#define GET_MACRO_2(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME
#define FOR_EACH_2(action, x, ...) \
    GET_MACRO_2(__VA_ARGS__, \
            FE_2_10, FE_2_9, FE_2_8, FE_2_7, FE_2_6, \
            FE_2_5, FE_2_4, FE_2_3, FE_2_2, FE_2_1) \
            (action, x, __VA_ARGS__)

#endif
