#ifndef _ASM_X86_RMWcc
#define _ASM_X86_RMWcc

#define __CLOBBERS_MEM(clb...)	"memory", ## clb

#if !defined(__GCC_ASM_FLAG_OUTPUTS__) && defined(CC_HAVE_ASM_GOTO)

/* Use asm goto */

#define __GEN_RMWcc(fullop, var, cc, ...)				\
do {									\
	asm_volatile_goto (fullop "; j" #cc " %l[cc_label]"		\
			: : "m" (var), ## __VA_ARGS__ 			\
			: "memory" : cc_label);				\
	return 0;							\
cc_label:								\
	return 1;							\
} while (0)

#define GEN_UNARY_RMWcc(op, var, arg0, cc) 				\
	__GEN_RMWcc(op " " arg0, var, cc)

#define GEN_BINARY_RMWcc(op, var, vcon, val, arg0, cc)			\
	__GEN_RMWcc(op " %1, " arg0, var, cc, vcon (val))

#else /* defined(__GCC_ASM_FLAG_OUTPUTS__) || !defined(CC_HAVE_ASM_GOTO) */

/* Use flags output or a set instruction */

#define __GEN_RMWcc(fullop, var, cc, ...)				\
do {									\
	bool c;								\
	asm volatile (fullop ";" CC_SET(cc)				\
			: "+m" (var), CC_OUT(cc) (c)			\
			: __VA_ARGS__ : "memory");			\
	return c;							\
} while (0)

#define GEN_UNARY_RMWcc(op, var, arg0, cc)				\
	__GEN_RMWcc(op " " arg0, var, cc, __CLOBBERS_MEM())

#define GEN_UNARY_SUFFIXED_RMWcc(op, suffix, var, arg0, cc, clobbers...)\
	__GEN_RMWcc(op " " arg0 "\n\t" suffix, var, cc,			\
		    __CLOBBERS_MEM(clobbers))

#define GEN_BINARY_RMWcc(op, var, vcon, val, arg0, cc)			\
	__GEN_RMWcc(op __BINARY_RMWcc_ARG arg0, var, cc,		\
		    __CLOBBERS_MEM(), vcon (val))

#define GEN_BINARY_SUFFIXED_RMWcc(op, suffix, var, vcon, val, arg0, cc,	\
				  clobbers...)				\
	__GEN_RMWcc(op __BINARY_RMWcc_ARG arg0 "\n\t" suffix, var, cc,	\
		    __CLOBBERS_MEM(clobbers), vcon (val))

#endif /* _ASM_X86_RMWcc */
