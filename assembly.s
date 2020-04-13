.global _Z2a1j
.global _Z2a2j

_Z2a1j:
	ldr	r1,[r0]
	mov	r2,#0
.L1:
	add	r0,#1
	cmp	r1,r2
	bne	.L1
	bx	lr
_Z2a2j:
	ldr	r1,[r0]
.L2:
	subs	r1,#1
	bne	.L2
	bx	lr
