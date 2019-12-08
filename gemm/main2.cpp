#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define DECOMPOSE_K\
    int k8 = k >> 3;\
    int k8_even = (k8 % 2 == 0) ? 0: 1;\
    k -= (k8 << 3);\
    int k4 = k >> 2;\
    k -= (k4 << 2);\
    int k2 = k >> 1;\
    k -= (k2 << 1);\
    int k1 = k;

#define DECOMPOSE_N\
    int n4 = n >> 2;\
    n -= (n4 << 2);\
    int n2 = n >> 1;\
    n -= (n2 << 1);\
    int n1 = n;

static void reorder_b(const int8_t* b, int8_t* sb, const int k, const int n, const int ldx) {

    int i = 0;
    for (; i+3 < n; i += 4) {
        const int8_t *p0 = b + i;
        const int8_t *p1 = b + 1 * ldx + i;
        const int8_t *p2 = b + 2 * ldx + i;
        const int8_t *p3 = b + 3 * ldx + i;

        const int8_t *p4 = b + 4 * ldx + i;
        const int8_t *p5 = b + 5 * ldx + i;
        const int8_t *p6 = b + 6 * ldx + i;
        const int8_t *p7 = b + 7 * ldx + i;

        int j = 0;
        for (; j+7 < k; j += 8) {
            sb[0]  = p0[0];
            sb[1]  = p1[0];
            sb[2]  = p2[0];
            sb[3]  = p3[0];
            sb[4]  = p4[0];
            sb[5]  = p5[0];
            sb[6]  = p6[0];
            sb[7]  = p7[0];

            sb[8]  = p0[1];
            sb[9]  = p1[1];
            sb[10] = p2[1];
            sb[11] = p3[1];
            sb[12] = p4[1];
            sb[13] = p5[1];
            sb[14] = p6[1];
            sb[15] = p7[1];

            sb[16] = p0[2];
            sb[17] = p1[2];
            sb[18] = p2[2];
            sb[19] = p3[2];
            sb[20] = p4[2];
            sb[21] = p5[2];
            sb[22] = p6[2];
            sb[23] = p7[2];

            sb[24] = p0[3];
            sb[25] = p1[3];
            sb[26] = p2[3];
            sb[27] = p3[3];
            sb[28] = p4[3];
            sb[29] = p5[3];
            sb[30] = p6[3];
            sb[31] = p7[3];

            sb += 32;
            p0 += 8 * ldx;
            p1 += 8 * ldx;
            p2 += 8 * ldx;
            p3 += 8 * ldx;
            p4 += 8 * ldx;
            p5 += 8 * ldx;
            p6 += 8 * ldx;
            p7 += 8 * ldx;
        }
        for (; j+3 < k; j += 4) {
            sb[0]  = p0[0];
            sb[1]  = p1[0];
            sb[2]  = p2[0];
            sb[3]  = p3[0];

            sb[4]  = p0[1];
            sb[5]  = p1[1];
            sb[6]  = p2[1];
            sb[7]  = p3[1];

            sb[8]  = p0[2];
            sb[9]  = p1[2];
            sb[10] = p2[2];
            sb[11] = p3[2];

            sb[12] = p0[3];
            sb[13] = p1[3];
            sb[14] = p2[3];
            sb[15] = p3[3];

            sb += 16;
            p0 += 4 * ldx;
            p1 += 4 * ldx;
            p2 += 4 * ldx;
            p3 += 4 * ldx;
        }
        for (; j+1 < k; j += 2) {
            sb[0] = p0[0];
            sb[1] = p1[0];
            sb[2] = p0[1];
            sb[3] = p1[1];
            sb[4] = p0[2];
            sb[5] = p1[2];
            sb[6] = p0[3];
            sb[7] = p1[3];

            sb += 8;
            p0 += 2 * ldx;
            p1 += 2 * ldx;
        }
        for (; j < k; ++j) {
            sb[0] = p0[0];
            sb[1] = p0[1];
            sb[2] = p0[2];
            sb[3] = p0[3];

            sb += 4;
            p0 += ldx;
        }
    }
    for (; i+1 < n; i += 2) {
        const int8_t *p0 = b + i;
        const int8_t *p1 = b + 1 * ldx + i;
        const int8_t *p2 = b + 2 * ldx + i;
        const int8_t *p3 = b + 3 * ldx + i;

        const int8_t *p4 = b + 4 * ldx + i;
        const int8_t *p5 = b + 5 * ldx + i;
        const int8_t *p6 = b + 6 * ldx + i;
        const int8_t *p7 = b + 7 * ldx + i;

        int j = 0;
        for (; j+7 < k; j += 8) {
            sb[0]  = p0[0];
            sb[1]  = p1[0];
            sb[2]  = p2[0];
            sb[3]  = p3[0];
            sb[4]  = p4[0];
            sb[5]  = p5[0];
            sb[6]  = p6[0];
            sb[7]  = p7[0];

            sb[8]  = p0[1];
            sb[9]  = p1[1];
            sb[10] = p2[1];
            sb[11] = p3[1];
            sb[12] = p4[1];
            sb[13] = p5[1];
            sb[14] = p6[1];
            sb[15] = p7[1];

            sb += 16;
            p0 += 8 * ldx;
            p1 += 8 * ldx;
            p2 += 8 * ldx;
            p3 += 8 * ldx;
            p4 += 8 * ldx;
            p5 += 8 * ldx;
            p6 += 8 * ldx;
            p7 += 8 * ldx;
        }
        for (; j+3 < k; j += 4) {
            sb[0]  = p0[0];
            sb[1]  = p1[0];
            sb[2]  = p2[0];
            sb[3]  = p3[0];

            sb[4]  = p0[1];
            sb[5]  = p1[1];
            sb[6]  = p2[1];
            sb[7]  = p3[1];

            sb += 8;
            p0 += 4 * ldx;
            p1 += 4 * ldx;
            p2 += 4 * ldx;
            p3 += 4 * ldx;
        }
        for (; j+1 < k; j += 2) {
            sb[0] = p0[0];
            sb[1] = p1[0];
            sb[2] = p0[1];
            sb[3] = p1[1];

            sb += 4;
            p0 += 2 * ldx;
            p1 += 2 * ldx;
        }
        for (; j < k; ++j) {
            sb[0] = p0[0];
            sb[1] = p0[1];

            sb += 2;
            p0 += ldx;
        }
    }
    for (; i < n; ++i) {
        const int8_t *p0 = b + i;
        const int8_t *p1 = b + 1 * ldx + i;
        const int8_t *p2 = b + 2 * ldx + i;
        const int8_t *p3 = b + 3 * ldx + i;
        const int8_t *p4 = b + 4 * ldx + i;
        const int8_t *p5 = b + 5 * ldx + i;
        const int8_t *p6 = b + 6 * ldx + i;
        const int8_t *p7 = b + 7 * ldx + i;

        int j = 0;
        for (; j+7 < k; j += 8) {
            sb[0]  = p0[0];
            sb[1]  = p1[0];
            sb[2]  = p2[0];
            sb[3]  = p3[0];
            sb[4]  = p4[0];
            sb[5]  = p5[0];
            sb[6]  = p6[0];
            sb[7]  = p7[0];

            sb += 8;
            p0 += 8 * ldx;
            p1 += 8 * ldx;
            p2 += 8 * ldx;
            p3 += 8 * ldx;
            p4 += 8 * ldx;
            p5 += 8 * ldx;
            p6 += 8 * ldx;
            p7 += 8 * ldx;
        }
        for (; j+3 < k; j += 4) {
            sb[0]  = p0[0];
            sb[1]  = p1[0];
            sb[2]  = p2[0];
            sb[3]  = p3[0];

            sb += 4;
            p0 += 4 * ldx;
            p1 += 4 * ldx;
            p2 += 4 * ldx;
            p3 += 4 * ldx;
        }
        for (; j+1 < k; j += 2) {
            sb[0] = p0[0];
            sb[1] = p1[0];

            sb += 2;
            p0 += 2 * ldx;
            p1 += 2 * ldx;
        }
        for (; j < k; ++j) {
            sb[0] = p0[0];

            sb += 1;
            p0 += ldx;
        }
    }
}

static void reorder_a_c(int8_t* a, int8_t* sa, int m, const int k, const int ldx) {
    int i = 0;
    for (; i + 3 < m; i += 4) {
        int8_t *p0 = a;
        int8_t *p1 = a + ldx;
        int8_t *p2 = a + 2 * ldx;
        int8_t *p3 = a + 3 * ldx;

        int j = 0;
        for (; j + 7 < k; j += 8) {
            asm volatile (
                "ld1 {v0.8b}, [%0], #8  \n" 
                "ld1 {v1.8b}, [%1], #8  \n" 
                "ld1 {v2.8b}, [%2], #8  \n" 
                "ld1 {v3.8b}, [%3], #8  \n" 
                "st1 {v0.8b, v1.8b, v2.8b, v3.8b}, [%4], #32\n"
                :   "=r"(p0),
                    "=r"(p1),
                    "=r"(p2),
                    "=r"(p3),
                    "=r"(sa)
                :   "0"(p0),
                    "1"(p1),
                    "2"(p2),
                    "3"(p3),
                    "4"(sa)
                : "cc", "memory", "v0", "v1", "v2", "v3"
            );
        }

        if (j + 3 < k) {
            j += 4;
            asm volatile (
                "ld1 {v0.8b}, [%0]  \n" 
                "add %0, %0, #4     \n"
                "ld1 {v1.8b}, [%1]  \n" 
                "add %1, %1, #4     \n"
                "ld1 {v2.8b}, [%2]  \n" 
                "add %2, %2, #4     \n"
                "ld1 {v3.8b}, [%3]  \n" 
                "add %3, %3, #4     \n"
                "trn1 v0.2s, v0.2s, v1.2s   \n"
                "st1 {v0.8b}, [%4], #8      \n"
                "trn1 v2.2s, v2.2s, v3.2s   \n"
                "st1 {v2.8b}, [%4], #8      \n"
                :   "=r"(p0),
                    "=r"(p1),
                    "=r"(p2),
                    "=r"(p3),
                    "=r"(sa)
                :   "0"(p0),
                    "1"(p1),
                    "2"(p2),
                    "3"(p3),
                    "4"(sa)
                : "cc", "memory", "v0", "v1", "v2", "v3"
            );
        }

        if (j + 1 < k) {
            j += 2;
            asm volatile (
                "ld1 {v0.8b}, [%0]  \n" 
                "add %0, %0, #2     \n"
                "ld1 {v1.8b}, [%1]  \n" 
                "add %1, %1, #2     \n"
                "ld1 {v2.8b}, [%2]  \n" 
                "add %2, %2, #2     \n"
                "ld1 {v3.8b}, [%3]  \n" 
                "add %3, %3, #2     \n"
                "trn1 v0.4h, v0.4h, v1.4h   \n"
                "trn1 v2.4h, v2.4h, v3.4h   \n"
                "trn1 v0.2s, v0.2s, v2.2s   \n"
                "st1 {v0.8b}, [%4], #8      \n"
                :   "=r"(p0),
                    "=r"(p1),
                    "=r"(p2),
                    "=r"(p3),
                    "=r"(sa)
                :   "0"(p0),
                    "1"(p1),
                    "2"(p2),
                    "3"(p3),
                    "4"(sa)
                : "cc", "memory", "v0", "v1", "v2", "v3"
            );
        }

        if (j < k) {
            *sa++ = *p0;
            *sa++ = *p1;
            *sa++ = *p2;
            *sa++ = *p3;
        }

        a += 4 * ldx;
    }

    if (i + 1 < m) {
        i += 2;
        int8_t *p0 = a;
        int8_t *p1 = a + ldx;

        int j = 0;
        for (; j + 7 < k; j += 8) {
            asm volatile (
                "ld1 {v0.8b}, [%0], #8  \n" 
                "ld1 {v1.8b}, [%1], #8  \n" 
                "st1 {v0.8b, v1.8b}, [%2], #16\n"
                :   "=r"(p0),
                    "=r"(p1),
                    "=r"(sa)
                :   "0"(p0),
                    "1"(p1),
                    "2"(sa)
                : "cc", "memory", "v0", "v1"
            );
        }

        if (j + 3 < k) {
            j += 4;
            asm volatile (
                "ld1 {v0.8b}, [%0]  \n" 
                "add %0, %0, #4     \n"
                "ld1 {v1.8b}, [%1]  \n" 
                "add %1, %1, #4     \n"
                "trn1 v0.2s, v0.2s, v1.2s   \n"
                "st1 {v0.8b}, [%2], #8      \n"
                :   "=r"(p0),
                    "=r"(p1),
                    "=r"(sa)
                :   "0"(p0),
                    "1"(p1),
                    "2"(sa)
                : "cc", "memory", "v0", "v1"
            );
        }

        if (j + 1 < k) {
            j += 2;
            sa[0] = p0[0];
            sa[1] = p0[1];
            sa[2] = p1[0];
            sa[3] = p1[1];
            sa += 4;
            p0 += 2;
            p1 += 2;
        }

        if (j < k) {
            sa[0] = p0[0];
            sa[1] = p1[0];
            sa += 2;
        }

        a += 2 * ldx;
    }

    if (i < m) {
        memcpy(sa, a, sizeof(int8_t) * ldx);
    }
}

void int8kernel_m1_new(int32_t* dst, int8_t* sa, int8_t* sb, int m, int k, int n, int ldc) {
    int32_t *pc = dst;
    int8_t *pa = sa;
    int8_t *pb = sb;

    float* scales = nullptr;
    float* bias = nullptr;

    DECOMPOSE_K
    DECOMPOSE_N

    if (n4 > 0) {
        asm volatile(
        "m1_loopnd4:   \n"
        "    eor v8.16b, v8.16b, v8.16b   \n"
        "    eor v9.16b, v9.16b, v9.16b   \n"
        "    eor v10.16b, v10.16b, v10.16b\n"
        "    eor v11.16b, v11.16b, v11.16b\n"

        "    mov x8, %0  // PanelA\n"
        
        "    cmp %w4, #0       \n"
        "    beq m1_loopkd4_nd4\n"
        
        "    mov w19, %w4      \n"
        
        "    cmp %w3, #0       \n"
        "    beq m1_loopkd8_nd4_even // loop number is even \n"
        
        "    // start loopm1_kd8_nd4\n"
        "    subs w19, w19, #1        \n"
        "    ld1 {v4.8b, v5.8b, v6.8b, v7.8b}, [%1], #32 // load four lines of B\n"
        "    ld1 {v2.8b}, [%0], #8  // load two lines of PanelA\n"
        
        "    smull v0.8h, v4.8b, v2.8b  \n"
        "    saddlp v8.4s, v0.8h        \n"
        "    smull v0.8h, v5.8b, v2.8b  \n"
        "    saddlp v9.4s, v0.8h        \n"
        "    smull v0.8h, v6.8b, v2.8b  \n"
        "    saddlp v10.4s, v0.8h       \n"
        "    smull v0.8h, v7.8b, v2.8b  \n"
        "    saddlp v11.4s, v0.8h       \n"
        
        "    cmp w19, #0           \n"
        "    beq m1_loopkd8_nd4_end\n"
        
        "    m1_loopkd8_nd4_even:  \n"
        "        ld1 {v4.8b, v5.8b, v6.8b, v7.8b}, [%1], #32    \n"
        "        ld1 {v12.8b, v13.8b, v14.8b, v15.8b}, [%1], #32\n"
        
        "        ld1 {v2.8b, v3.8b}, [%0], #16  \n"
        
        "        smull v0.8h, v2.8b, v4.8b  \n"
        "        smlal v0.8h, v3.8b, v12.8b \n"
        "        sadalp v8.4s, v0.8h        \n"
        
        "        smull v1.8h, v2.8b, v5.8b  \n"
        "        smlal v1.8h, v3.8b, v13.8b \n"
        "        sadalp v9.4s, v1.8h        \n"
        
        "        smull v0.8h, v2.8b, v6.8b  \n"
        "        smlal v0.8h, v3.8b, v14.8b \n"
        "        sadalp v10.4s, v0.8h       \n"
        
        "        smull v1.8h, v2.8b, v7.8b  \n"
        "        smlal v1.8h, v3.8b, v15.8b \n"
        "        sadalp v11.4s, v1.8h       \n"
        
        "        subs w19, w19, #2         \n"
        "        bne m1_loopkd8_nd4_even   \n"
        
        "    m1_loopkd8_nd4_end:               \n"
        "        addp v8.4s, v8.4s, v9.4s   \n"
        "        addp v10.4s, v10.4s, v11.4s\n"
        "        addp v8.4s, v8.4s, v10.4s  \n"
        
        "        // start process kd4 kd2 kd1 cases\n"
        "    m1_loopkd4_nd4:                   \n"
        "        cmp %w5, #0                   \n"
        "        beq m1_loopkd2_nd4            \n"
        "        // start subkernel_m1n4k4  \n"
        "        ld1 {v4.8b, v5.8b}, [%1], #16  // load B4x4\n"
        "        sxtl v4.8h, v4.8b          \n"
        "        sxtl v5.8h, v5.8b          \n"
        "        mov v6.d[0], v4.d[1]       \n"
        "        mov v7.d[0], v5.d[1]       \n"
        
        "        ld1 {v2.8b}, [%0]  // load A1x4\n"
        "        add %0, %0, #4                 \n"
        "        sxtl v2.8h, v2.8b              \n"
        
        "        smull v12.4s, v2.4h, v4.4h \n"
        "        smull v13.4s, v2.4h, v6.4h \n"
        "        smull v14.4s, v2.4h, v5.4h \n"
        "        smull v15.4s, v2.4h, v7.4h \n"
        
        "        addp v12.4s, v12.4s, v13.4s\n"
        "        addp v14.4s, v14.4s, v15.4s\n"
        "        addp v12.4s, v12.4s, v14.4s\n"
        "        add v8.4s, v8.4s, v12.4s   \n"
        
        "    m1_loopkd2_nd4:           \n"
        "        cmp %w6, #0           \n"
        "        beq m1_loopkd1_nd4    \n"
        "        // start subkernel_m1n4k2\n"
        "        ld1 {v4.8b}, [%0]       // load A1x2   \n"
        "        add %0, %0, #2                         \n"
        "        ld1 {v0.8b}, [%1], #8   // load B2x4   \n"
        
        "        mov v4.h[1], v4.h[0]   \n"
        "        mov v4.s[1], v4.s[0]   \n"

        "        smull v0.8h, v0.8b, v4.8b  \n"
        "        sadalp v8.4s, v0.8h        \n"
        
        "    m1_loopkd1_nd4:       \n"
        "        cmp %w7, #0       \n"
        "        beq m1_loopnd4_end\n"
        "        // start subkernel_m1n4k1  \n"
        "        ld1 {v4.8b}, [%1]   // load B1x4\n"
        "        add %1, %1, #4     \n"
        "        ld1 {v2.8b}, [%0]   // load A1x1\n"
        "        add %0, %0, #1     \n"
        "        sxtl v4.8h, v4.8b  \n"
        "        sxtl v2.8h, v2.8b  \n"
        "        smlal v8.4s, v4.4h, v2.h[0]\n"
        
        "    m1_loopnd4_end:                \n"
        "        cmp %9, #0                 \n"
        "        beq m1_loopnd4_write       \n"
        "        ldr x24, [%9]              \n"
        "        // int32 => fp32           \n"
        "        scvtf v8.4s, v8.4s         \n"
        "        // fp32 *= scale_tm        \n"
        "        mov v12.s[0], w24          \n"
        "        fmul v8.4s, v8.4s, v12.s[0]\n"
        
        "        cmp %10, #0\n"
        "        beq m1_loopnd4_end_requant \n"
        
        "        // fp32 += bias_tm         \n"
        "        ldr x24, [%10]             \n"
        "        dup v15.4s, w24            \n"
        "        fadd v8.4s, v8.4s, v15.4s  \n"
        
        "        m1_loopnd4_end_requant:\n"
        "            // fp32 -> int32   \n"
        "            fcvtas v8.4s, v8.4s\n"
        "            // int32 -> int16  \n"
        "            sqxtn v6.4h, v8.4s \n"
        "            // int16 -> int8   \n"
        "            sqxtn v8.8b, v6.8h \n"
        "            // save            \n"
        "            st1 {v8.s}[0], [%2]\n"
        "            add %2, %2, #4     \n"
        "            b m1_loopnd4_finish\n"
        "    m1_loopnd4_write:          \n"
        "        st1 {v8.4s}, [%2], #16 \n"
        
        "    m1_loopnd4_finish:     \n"
        "        subs %w8, %w8, #1  \n"
        "        mov %0, x8         \n"
        "        bne m1_loopnd4     \n"
        : "=r"(pa),     // %0
          "=r"(pb),     // %1
          "=r"(pc),     // %2
          "=r"(k8_even),// %3 
          "=r"(k8),     // %4
          "=r"(k4),     // %5
          "=r"(k2),     // %6
          "=r"(k1),     // %7
          "=r"(n4),     // %8
          "=r"(scales), // %9
          "=r"(bias)    // %10
        : "0"(pa),
          "1"(pb),
          "2"(pc),
          "3"(k8_even),
          "4"(k8),     
          "5"(k4),     
          "6"(k2),     
          "7"(k1),    
          "8"(n4),    
          "9"(scales),
          "10"(bias)   
        : "cc", "memory", "x8", "w19", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"
        );
    }

    if (n2 > 0) {
        asm volatile(
        "m1_nd2_start:                  \n"
        "    eor v8.16b, v8.16b, v8.16b   \n"
        "    eor v9.16b, v9.16b, v9.16b   \n"
        "    eor v10.16b, v10.16b, v10.16b\n"
        "    eor v11.16b, v11.16b, v11.16b\n"

        "    mov x8, %0  // PanelA\n"
        
        "    cmp %w4, #0                  \n"
        "    beq m1_loopkd4_nd2  // k <= 7\n"
        
        "    mov w19, %w4\n"
        "    cmp %w3, #0 \n"
        "    beq m1_loopkd8_nd2_even  // loop number is even \n"
        
        "    // start loopmd1_kd8_nd2   \n"
        "    subs w19, w19, #1          \n"
        "    ld1 {v4.8b, v5.8b}, [%1], #16  // load two lines of B\n"
        "    ld1 {v2.8b}, [%0], #8  // load two lines of PanelA\n"
        "    smull v0.8h, v4.8b, v2.8b  \n"
        "    saddlp v8.4s, v0.8h        \n"
        "    smull v0.8h, v5.8b, v2.8b  \n"
        "    saddlp v9.4s, v0.8h        \n"
        
        "    cmp w19, #0        \n"
        "    beq m1_loopkd8_nd2_end\n"
        
        "    m1_loopkd8_nd2_even:  \n"
        "        ld1 {v4.8b, v5.8b, v6.8b, v7.8b}, [%1], #32\n"
        
        "        ld1 {v2.8b, v3.8b}, [%0], #16  \n"
        
        "        smull v0.8h, v2.8b, v4.8b  \n"
        "        smlal v0.8h, v3.8b, v6.8b  \n"
        "        sadalp v8.4s, v0.8h        \n"
        
        "        smull v1.8h, v2.8b, v5.8b  \n"
        "        smlal v1.8h, v3.8b, v7.8b  \n"
        "        sadalp v9.4s, v1.8h        \n"
        
        "        subs x19, x19, #2      \n"
        "        bne m1_loopkd8_nd2_even   \n"
        
        "    m1_loopkd8_nd2_end:               \n"
        "        addp v8.4s, v8.4s, v9.4s   \n"
        "        addp v8.4s, v8.4s, v8.4s   \n"
        
        "        // start process kd4 kd2 kd1 cases \n"
        "    m1_loopkd4_nd2:               \n"
        "        cmp %w5, 0                \n"
        "        beq m1_loopkd2_nd2        \n"
        "        // start subkernel_m1n2k4          \n"
        "        ld1 {v4.8b}, [%1], #8  // load B4x2\n"
        "        sxtl v4.8h, v4.8b      \n"
        "        mov v6.d[0], v4.d[1]   \n"
        
        "        ld1 {v2.8b}, [%0]      // load A1x4\n"
        "        add %0, %0, #4     \n"
        "        sxtl v2.8h, v2.8b  \n"
        
        "        smull v9.4s, v2.4h, v4.4h  \n"
        "        smull v10.4s, v2.4h, v6.4h \n"
        
        "        addp v9.4s, v9.4s, v10.4s  \n"
        "        addp v9.4s, v9.4s, v9.4s   \n"
        "        add v8.4s, v8.4s, v9.4s    \n"
        
        "    m1_loopkd2_nd2:   \n"
        "        cmp %w6, 0 \n"
        "        beq m1_loopkd1_nd2            \n"
        "        // start subkernel_m1n2k2  \n"
        "        ld1 {v4.8b}, [%0]   // load A1x2\n"
        "        add %0, %0, #2 \n"
        "        ld1 {v0.8b}, [%1]   // load B2x2\n"
        "        add %1, %1, #4 \n"
        
        "        mov v4.h[1], v4.h[0]   \n"
        
        "        smull v0.8h, v4.8b, v0.8b  \n"
        "        saddlp v0.4s, v0.8h        \n"
        "        add v8.4s, v8.4s, v0.4s    \n"
        
        "    m1_loopkd1_nd2:                \n"
        "        cmp %w7, 0                 \n"
        "        beq m1_loopnd2_end         \n"
        "        // start subkernel_m1n2k1  \n"
        "        ld1 {v4.8b}, [%1]   // load B1x2\n"
        "        add %1, %1, #2             \n"
        "        ld1 {v2.8b}, [%0]   // load A1x1\n"
        "        add %0, %0, #2             \n"
        "        sxtl v4.8h, v4.8b          \n"
        "        sxtl v2.8h, v2.8b          \n"
        "        smlal v8.4s, v4.4h, v2.h[0]\n"
        
        "    m1_loopnd2_end:            \n"
        "        cmp %9, #0             \n"
        "        beq m1_loopnd2_write   \n"
        "        // v12: s0 s1          \n"
        "        ldr x24, [%9]          \n"
        "        mov v12.s[0], w24      \n"
        "        mov v12.s[1], v12.s[0] \n"
        
        "        // int32 => fp32           \n"
        "        scvtf v8.2s, v8.2s         \n"
        "        // fp32 *= scale_tm        \n"
        "        fmul v8.2s, v8.2s, v12.2s  \n"
        
        "        cmp %10, #0                \n"
        "        beq m1_loopnd2_end_requant \n"
        
        "        // fp32 += bias_tm         \n"
        "        ldr x24, [%10]             \n"
        "        mov v12.s[0], w24          \n"
        "        mov v12.s[1], v12.s[0]     \n"
        "        fadd v8.4s, v8.4s, v12.4s  \n"
        
        "        m1_loopnd2_end_requant:\n"
        "            // fp32 -> int32   \n"
        "            fcvtas v8.2s, v8.2s\n"
        "            // int32 -> int16  \n"
        "            sqxtn v8.4h, v8.4s \n"
        "            // int16 -> int8   \n"
        "            sqxtn v8.8b, v8.8h \n"
        "            // save            \n"
        "            st1 {v8.h}[0], [%2]\n"
        "            add %2, %2, #2     \n"
        "    m1_loopnd2_write:          \n"
        "        st1 {v8.2s}, [%2], #8  \n"

        "    m1_loopnd2_finish: \n"
        "        mov %0, x8     \n"
        : "=r"(pa),     // %0
          "=r"(pb),     // %1
          "=r"(pc),     // %2
          "=r"(k8_even),// %3 
          "=r"(k8),     // %4
          "=r"(k4),     // %5
          "=r"(k2),     // %6
          "=r"(k1),     // %7
          "=r"(n4),     // %8
          "=r"(scales), // %9
          "=r"(bias)    // %10
        : "0"(pa),
          "1"(pb),
          "2"(pc),
          "3"(k8_even),
          "4"(k8),     
          "5"(k4),     
          "6"(k2),     
          "7"(k1),    
          "8"(n4),    
          "9"(scales),
          "10"(bias)   
        : "cc", "memory", "x8", "w19", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"
        );
    
    }

    if (n1 > 0) {
    asm volatile (
        "m1_nd1_start:                    \n"
        "    eor v8.16b, v8.16b, v8.16b   \n"
        "    eor v9.16b, v9.16b, v9.16b   \n"
        "    eor v10.16b, v10.16b, v10.16b\n"
        "    eor v11.16b, v11.16b, v11.16b\n"

        "    cmp %w4, #0                    \n"
        "    beq m1_loopkd4_nd1 // k <= 7   \n"
        
        "    mov w19, %w4\n"

        "    cmp %w3, #0 \n"
        "    beq m1_loopkd8_nd1_even // loop number is even \n"
        
        "    // start loopkd8_nd1                   \n"
        "    subs w19, w19, #1                      \n"
        "    ld1 {v4.8b}, [%1], #8  // load B line  \n"
        "    ld1 {v2.8b}, [%0], #8  // load A line  \n"
        "    smull v0.8h, v4.8b, v2.8b              \n"
        "    saddlp v8.4s, v0.8h                    \n"
        
        "    cmp w19, #0           \n"
        "    beq m1_loopkd8_nd1_end\n"
        
        "    m1_loopkd8_nd1_even:                  \n"
        "        ld1 {v4.8b, v5.8b}, [%1], #16  \n"
        "        ld1 {v24.8b, v25.8b}, [%0], #16\n"

        "        smull v0.8h, v24.8b, v4.8b \n"
        "        smlal v0.8h, v25.8b, v5.8b \n"
        "        sadalp v8.4s, v0.8h        \n"
        
        "        subs w19, w19, #2          \n"
        "        bne m1_loopkd8_nd1_even    \n"
        
        "    m1_loopkd8_nd1_end:            \n"
        "        addp v8.4s, v8.4s, v8.4s   \n"
        "        addp v8.4s, v8.4s, v8.4s   \n"
        
        "        // start process kd4 kd2 kd1 cases\n"
        "    m1_loopkd4_nd1:                \n"
        "        cmp %w5, 0                 \n"
        "        beq m1_loopkd2_nd1         \n"
        "        // start subkernel_m1n1k4  \n"
        "        ld1 {v4.8b}, [%1]  // load B4x1\n"
        "        add %1, %1, #4             \n"
        "        sxtl v4.8h, v4.8b   // extend B4x1 to v4\n"
        
        "        ld1 {v2.8b}, [%0]  // load A1x4\n"
        "        add %0, %0, #4             \n"
        "        sxtl v2.8h, v2.8b          \n"
        
        "        smull v9.4s, v2.4h, v4.4h  \n"
        "        addp v9.4s, v9.4s, v9.4s   \n"
        "        addp v9.4s, v9.4s, v9.4s   \n"
        "        add v8.4s, v8.4s, v9.4s    \n"
        
        "    m1_loopkd2_nd1:   \n"
        "        cmp %w6, 0    \n"
        "        beq m1_loopkd1_nd1         \n"
        "        // start subkernel_m1n1k2  \n"
        "        ld1 {v4.8b}, [%0]   // load A1x2\n"
        "        add %0, %0, #2             \n"
        "        ld1 {v0.8b}, [%1]   // load B2x1\n"
        "        add %1, %1, #2             \n"
        
        "        smull v0.8h, v0.8b, v4.8b  \n"
        "        saddlp v0.4s, v0.8h        \n"

        "        add v8.4s, v8.4s, v0.4s    \n"
        
        "    m1_loopkd1_nd1:                \n"
        "        cmp %w7, 0                 \n"
        "        beq m1_loopnd1_end         \n"
        "        // start subkernel_m1n1k1  \n"
        
        "        ld1 {v0.8b}, [%1]    // load B1x1  \n"
        "        add %1, %1, #1                     \n"
        
        "        ld1 {v1.8b}, [%0]   // load A1x1   \n"
        "        add %0, %0, #1                     \n"

        "        sxtl v1.8h, v1.8b  \n"
        "        sxtl v0.8h, v0.8b  \n"
        
        "        smull v0.4s, v1.4h, v0.h[0]    \n"

        "        add v8.4s, v8.4s, v0.4s    \n"
        
        "    m1_loopnd1_end:            \n"
        "        cmp %9, #0             \n"
        "        beq m1_loopnd1_write   \n"
        "        // v12: s0 s1      \n"
        "        ldr x24, [%9]      \n"
        "        // int32 => fp32   \n"
        "        scvtf v8.2s, v8.2s \n"
        "        // fp32 *= scale_tm\n"
        "        mov v12.s[0], w24  \n"
        "        fmul v8.2s, v8.2s, v12.2s \n"
        
        "        cmp %10, #0                \n"
        "        beq m1_loopnd1_end_requant \n"
        
        "        // fp32 += bias_tm         \n"
        "        ldr x24, [%10]             \n"
        "        mov v12.s[0], w24          \n"
        "        fadd v8.2s, v8.2s, v12.2s  \n"
        
        "        m1_loopnd1_end_requant:   \n"
        "            // fp32 -> int32   \n"
        "            fcvtas v8.2s, v8.2s\n"
        "            // int32 -> int16  \n"
        "            sqxtn v8.4h, v8.4s \n"
        "            // int16 -> int8   \n"
        "            sqxtn v8.8b, v8.8h \n"
        "            // save            \n"
        "            st1 {v8.b}[0], [%2]\n"
        "            b m1_finish        \n"

        "    m1_loopnd1_write:          \n"
        "        st1 {v8.s}[0], [%2]    \n"
        "    m1_finish:                 \n"
        "        mov x0, #0             \n"
        : "=r"(pa),     // %0
          "=r"(pb),     // %1
          "=r"(pc),     // %2
          "=r"(k8_even),// %3 
          "=r"(k8),     // %4
          "=r"(k4),     // %5
          "=r"(k2),     // %6
          "=r"(k1),     // %7
          "=r"(n4),     // %8
          "=r"(scales), // %9
          "=r"(bias)    // %10
        : "0"(pa),
          "1"(pb),
          "2"(pc),
          "3"(k8_even),
          "4"(k8),     
          "5"(k4),     
          "6"(k2),     
          "7"(k1),    
          "8"(n4),    
          "9"(scales),
          "10"(bias)   
        : "cc", "memory", "x8", "w19", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"
        );
    }
}

void int8kernel_m2_new(int32_t* dst, int8_t* sa, int8_t* sb, int m, int k, int n, int ldc) {
    int32_t *pc = dst;
    int8_t *pa = sa;
    int8_t *pb = sb;

    float* scales = nullptr;
    float* bias = nullptr;

    int32_t *pc0 = dst;
    int32_t *pc1 = pc0 + ldc;

    DECOMPOSE_K
    DECOMPOSE_N

    if (n4 > 0) {
        asm volatile(
        "m2_loopnd4:                        \n"
        "    eor v8.16b, v8.16b, v8.16b     \n"
        "    eor v9.16b, v9.16b, v9.16b     \n"
        "    eor v10.16b, v10.16b, v10.16b  \n"
        "    eor v11.16b, v11.16b, v11.16b  \n"
        "    eor v12.16b, v12.16b, v12.16b  \n"
        "    eor v13.16b, v13.16b, v13.16b  \n"
        "    eor v14.16b, v14.16b, v14.16b  \n"
        "    eor v15.16b, v15.16b, v15.16b  \n"

        "    eor v16.16b, v16.16b, v16.16b  \n"
        "    eor v17.16b, v17.16b, v17.16b  \n"
        "    eor v18.16b, v18.16b, v18.16b  \n"
        "    eor v19.16b, v19.16b, v19.16b  \n"
        "    eor v20.16b, v20.16b, v20.16b  \n"
        "    eor v21.16b, v21.16b, v21.16b  \n"
        "    eor v22.16b, v22.16b, v22.16b  \n"
        "    eor v23.16b, v23.16b, v23.16b  \n"

        "    mov x8, %0  // PanelA  \n"
        
        "    cmp %w5, #0            \n"
        "    beq m2_loopkd4_nd4     \n"
        
        "    mov w17, %w5           \n"
        
        "    cmp %w4, #0            \n"
        "    beq m2_loopkd8_nd4_even // loop number is even \n"
        
        "    // start loopm2_kd8_nd4\n"
        "    subs w17, w17, #1      \n"
        "    ld1 {v4.8b, v5.8b, v6.8b, v7.8b}, [%1], #32 // load four lines of B\n"
        "    ld1 {v2.8b, v3.8b}, [%0], #16  // load two lines of PanelA         \n"
        "    smull v0.8h, v4.8b, v2.8b  \n"
        "    smull v1.8h, v4.8b, v3.8b  \n"
        "    saddlp v8.4s, v0.8h        \n"
        "    saddlp v12.4s, v1.8h       \n"
        "    smull v0.8h, v5.8b, v2.8b  \n"
        "    smull v1.8h, v5.8b, v3.8b  \n"
        "    saddlp v9.4s, v0.8h        \n"
        "    saddlp v13.4s, v1.8h       \n"
        "    smull v0.8h, v6.8b, v2.8b  \n"
        "    smull v1.8h, v6.8b, v3.8b  \n"
        "    saddlp v10.4s, v0.8h       \n"
        "    saddlp v14.4s, v1.8h       \n"
        "    smull v0.8h, v7.8b, v2.8b  \n"
        "    smull v1.8h, v7.8b, v3.8b  \n"
        "    saddlp v11.4s, v0.8h       \n"
        "    saddlp v15.4s, v1.8h       \n"
        
        "    cmp w17, #0                \n"
        "    beq m2_loopkd8_nd4_end        \n"
        
        "    m2_loopkd8_nd4_even:                  \n"
        "        add x12, %1, #32               \n"
        "        ld1 {v4.8b, v5.8b}, [%1], #16  \n"
        "        ld1 {v2.8b, v3.8b}, [%0], #16  \n"
        
        "        smull v0.8h, v4.8b, v2.8b      \n"
        "        smull v1.8h, v5.8b, v2.8b      \n"
        
        "        ld1 {v6.8b, v7.8b}, [x12], #16 \n"
        "        ld1 {v24.8b, v25.8b}, [%0], #16\n"
        
        "        smlal v0.8h, v6.8b, v24.8b \n"
        "        smlal v1.8h, v7.8b, v24.8b \n"
        
        "        sadalp v8.4s, v0.8h\n"
        "        sadalp v9.4s, v1.8h\n"

        "        smull v0.8h, v4.8b, v3.8b  \n"
        "        smull v1.8h, v5.8b, v3.8b  \n"
        "        smlal v0.8h, v6.8b, v25.8b \n"
        "        smlal v1.8h, v7.8b, v25.8b \n"
        
        "        sadalp v12.4s, v0.8h\n"
        "        sadalp v13.4s, v1.8h\n"
        
        "        // start v10v11, v14v15, v18v19, v22v23, error here!\n"
        "        ld1 {v4.8b, v5.8b}, [%1], #16  \n"
        "        smull v0.8h, v4.8b, v2.8b      \n"
        "        smull v1.8h, v5.8b, v2.8b      \n"
        "        ld1 {v6.8b, v7.8b}, [x12], #16 \n"
        "        smlal v0.8h, v6.8b, v24.8b     \n"
        "        smlal v1.8h, v7.8b, v24.8b     \n"
        "        sadalp v10.4s, v0.8h           \n"
        "        sadalp v11.4s, v1.8h           \n"
        
        "        smull v0.8h, v4.8b, v3.8b  \n"
        "        smull v1.8h, v5.8b, v3.8b  \n"
        "        smlal v0.8h, v6.8b, v25.8b \n"
        "        smlal v1.8h, v7.8b, v25.8b \n"
        "        sadalp v14.4s, v0.8h       \n"
        "        sadalp v15.4s, v1.8h       \n"
        
        "        add %1, %1, #32        \n"
        "        subs w17, w17, #2      \n"
        "        bne m2_loopkd8_nd4_even   \n"
        
        "    m2_loopkd8_nd4_end:               \n"
        "        addp v8.4s, v8.4s, v9.4s   \n"
        "        addp v10.4s, v10.4s, v11.4s\n"
        "        addp v12.4s, v12.4s, v13.4s\n"
        "        addp v14.4s, v14.4s, v15.4s\n"
        
        "        addp v8.4s, v8.4s, v10.4s  \n"
        "        addp v9.4s, v12.4s, v14.4s \n"
        
        "        // start process kd4 kd2 kd1 cases \n"
        "    m2_loopkd4_nd4:                \n"
        "        cmp %w6, #0                \n"
        "        beq m2_loopkd2_nd4         \n"
        "        // start subkernel_m2n4k4  \n"
        "        ld1 {v4.8b, v5.8b}, [%1], #16  // load B4x4\n"
        "        sxtl v4.8h, v4.8b          \n"
        "        sxtl v5.8h, v5.8b          \n"
        "        mov v6.d[0], v4.d[1]       \n"
        "        mov v7.d[0], v5.d[1]       \n"
        
        "        ld1 {v2.8b}, [%0], #8  // load A2x4\n"
        "        sxtl v2.8h, v2.8b          \n"
        "        mov v3.d[0], v2.d[1]       \n"
        
        "        smull v12.4s, v2.4h, v4.4h \n"
        "        smull v13.4s, v2.4h, v6.4h \n"
        "        smull v14.4s, v2.4h, v5.4h \n"
        "        smull v15.4s, v2.4h, v7.4h \n"
        
        "        addp v12.4s, v12.4s, v13.4s\n"
        "        addp v14.4s, v14.4s, v15.4s\n"
        "        addp v12.4s, v12.4s, v14.4s\n"
        "        add v8.4s, v8.4s, v12.4s   \n"
        
        "        smull v16.4s, v3.4h, v4.4h \n"
        "        smull v17.4s, v3.4h, v6.4h \n"
        "        smull v18.4s, v3.4h, v5.4h \n"
        "        smull v19.4s, v3.4h, v7.4h \n"
        
        "        addp v16.4s, v16.4s, v17.4s\n"
        "        addp v18.4s, v18.4s, v19.4s\n"
        "        addp v16.4s, v16.4s, v18.4s\n"
        "        add v9.4s, v9.4s, v16.4s   \n"
        
        "    m2_loopkd2_nd4:                \n"
        "        cmp %w7, #0                \n"
        "        beq m2_loopkd1_nd4         \n"
        "        // start subkernel_m2n4k2  \n"
        "        ld1 {v4.8b}, [%0]       // load A2x2   \n"
        "        add %0, %0, #4             \n"
        "        ld1 {v0.8b}, [%1], #8   // load B2x4   \n"
        "                            // 00 11 22 33 \n"
        "        rev32 v1.4h, v0.4h  // 11 00 33 22 \n"
        "        rev64 v2.2s, v0.2s  // 22 33 00 11 \n"
        "        rev64 v3.4h, v0.4h  // 33 22 11 00 \n"
        
        "        smull v12.8h, v4.8b, v0.8b \n"
        "        smull v13.8h, v4.8b, v1.8b \n"
        "        smull v14.8h, v4.8b, v2.8b \n"
        "        smull v15.8h, v4.8b, v3.8b \n"
        
        "        saddlp v12.4s, v12.8h  \n"
        "        saddlp v13.4s, v13.8h  \n"
        "        saddlp v14.4s, v14.8h  \n"
        "        saddlp v15.4s, v15.8h  \n"
        
        "        mov v16.s[0], v12.s[0] \n"
        "        mov v16.s[1], v13.s[0] \n"
        "        mov v16.s[2], v14.s[0] \n"
        "        mov v16.s[3], v15.s[0] \n"
        
        "        mov v17.s[0], v13.s[1] \n"
        "        mov v17.s[1], v12.s[1] \n"
        "        mov v17.s[2], v15.s[1] \n"
        "        mov v17.s[3], v14.s[1] \n"

        "        add v8.4s, v8.4s, v16.4s   \n"
        "        add v9.4s, v9.4s, v17.4s   \n"
        
        "    m2_loopkd1_nd4:            \n"
        "        cmp %w8, #0            \n"
        "        beq m2_loopnd4_end     \n"
        "        // start subkernel_m2n4k1  \n"
        "        ld1 {v4.8b}, [%1]   // load B1x4\n"
        "        add %1, %1, #4         \n"
        "        ld1 {v2.8b}, [%0]   // load A2x1\n"
        "        add %0, %0, #2         \n"
        "        sxtl v4.8h, v4.8b      \n"
        "        sxtl v2.8h, v2.8b      \n"
        "        smlal v8.4s, v4.4h, v2.h[0]\n"
        "        smlal v9.4s, v4.4h, v2.h[1]\n"
        
        "    m2_loopnd4_end:           \n"
        "        cmp %10, #0           \n"
        "        beq m2_loopnd4_write  \n"

        "        ld1 {v12.2s}, [%10]        \n"
        "        // int32 => fp32           \n"
        "        scvtf v8.4s, v8.4s         \n"
        "        scvtf v9.4s, v9.4s         \n"
        "        // fp32 *= scale_tm        \n"
        "        fmul v8.4s, v8.4s, v12.s[0]\n"
        "        fmul v9.4s, v9.4s, v12.s[1]\n"
        
        "        cmp %11, #0                \n"
        "        beq m2_loopnd4_end_requant \n"
        
        "        // fp32 += scales_tm       \n"
        "        ld1 {v14.2s}, [%11]        \n"
        "        dup v15.4s, v14.s[0]       \n"
        "        fadd v8.4s, v8.4s, v15.4s  \n"
        "        dup v15.4s, v14.s[1]       \n"
        "        fadd v9.4s, v9.4s, v15.4s  \n"
        
        "        m2_loopnd4_end_requant:    \n"
        "            // fp32 -> int32   \n"
        "            fcvtas v8.4s, v8.4s\n"
        "            fcvtas v9.4s, v9.4s\n"
        "            // int32 -> int16  \n"
        "            sqxtn v6.4h, v8.4s \n"
        "            sqxtn2 v6.8h, v9.4s\n"
        "            // int16 -> int8   \n"
        "            sqxtn v8.8b, v6.8h \n"
        "            // save                \n"
        "            st1 {v8.s}[0], [%2]    \n"
        "            add x10, x10, #4       \n"
        "            st1 {v8.s}[1], [%3]    \n"
        "            add x11, x11, #4       \n"
        "            b m2_loopnd4_finish    \n"
        "    m2_loopnd4_write:              \n"
        "        st1 {v8.4s}, [%2], #16     \n"
        "        st1 {v9.4s}, [%3], #16     \n"
        
        "    m2_loopnd4_finish:       \n"
        "        subs %w9, %w9, #1    \n"
        "        mov %0, x8           \n"
        "        bne m2_loopnd4       \n"
        : "=r"(pa),     // %0
          "=r"(pb),     // %1
          "=r"(pc0),    // %2
          "=r"(pc1),    // %3
          "=r"(k8_even),// %4 
          "=r"(k8),     // %5
          "=r"(k4),     // %6
          "=r"(k2),     // %7
          "=r"(k1),     // %8
          "=r"(n4),     // %9
          "=r"(scales), // %10
          "=r"(bias)    // %11
        : "0"(pa),
          "1"(pb),
          "2"(pc0),
          "3"(pc1),
          "4"(k8_even),
          "5"(k8),     
          "6"(k4),     
          "7"(k2),     
          "8"(k1),    
          "9"(n4),    
          "10"(scales),
          "11"(bias)   
        : "cc", "memory", "x8", "w17", "x12", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"
        );
    
    }

    if (n2 > 0) {
        asm volatile(
        "eor v8.16b, v8.16b, v8.16b     \n"
        "eor v9.16b, v9.16b, v9.16b     \n"
        "eor v10.16b, v10.16b, v10.16b  \n"
        "eor v11.16b, v11.16b, v11.16b  \n"
        "eor v12.16b, v12.16b, v12.16b  \n"
        "eor v13.16b, v13.16b, v13.16b  \n"
        "eor v14.16b, v14.16b, v14.16b  \n"
        "eor v15.16b, v15.16b, v15.16b  \n"

        "eor v16.16b, v16.16b, v16.16b  \n"
        "eor v17.16b, v17.16b, v17.16b  \n"
        "eor v18.16b, v18.16b, v18.16b  \n"
        "eor v19.16b, v19.16b, v19.16b  \n"
        "eor v20.16b, v20.16b, v20.16b  \n"
        "eor v21.16b, v21.16b, v21.16b  \n"
        "eor v22.16b, v22.16b, v22.16b  \n"
        "eor v23.16b, v23.16b, v23.16b  \n"

        "m2_nd2_start:                  \n"
        "    mov x8, %0  // PanelA      \n"
        
        "    cmp %w5, #0                \n"
        "    beq m2_loopkd4_nd2         \n"
        
        "    mov w17, %w5    \n"
        "    cmp %w4, #0     \n"
        "    beq m2_loopkd8_nd2_even  // loop number is even \n"
        
        "    // start loopmd2_kd8_nd2   \n"
        "    subs w17, w17, #1          \n"
        "    ld1 {v4.8b, v5.8b}, [%1], #16  // load two lines of B\n"
        "    ld1 {v2.8b, v3.8b}, [%0], #16  // load two lines of PanelA\n"
        "    smull v0.8h, v4.8b, v2.8b  \n"
        "    smull v1.8h, v4.8b, v3.8b  \n"
        "    saddlp v8.4s, v0.8h        \n"
        "    saddlp v12.4s, v1.8h       \n"
        "    smull v0.8h, v5.8b, v2.8b  \n"
        "    smull v1.8h, v5.8b, v3.8b  \n"
        "    saddlp v9.4s, v0.8h        \n"
        "    saddlp v13.4s, v1.8h       \n"
        
        "    cmp w17, #0        \n"
        "    beq m2_loopkd8_nd2_end\n"
        
        "    m2_loopkd8_nd2_even:  \n"
        "        ld1 {v4.8b, v5.8b}, [%1], #16  \n"
        "        ld1 {v2.8b, v3.8b}, [%0], #16  \n"
        
        "        smull v0.8h, v4.8b, v2.8b      \n"
        "        ld1 {v6.8b, v7.8b}, [%1], #16  \n"
        "        smull v1.8h, v5.8b, v2.8b      \n"
        "        ld1 {v24.8b, v25.8b}, [%0], #16\n"
        
        "        smlal v0.8h, v6.8b, v24.8b \n"
        "        smlal v1.8h, v7.8b, v24.8b \n"
        
        "        sadalp v8.4s, v0.8h\n"
        "        sadalp v9.4s, v1.8h\n"

        "        smull v0.8h, v4.8b, v3.8b  \n"
        "        smull v1.8h, v5.8b, v3.8b  \n"
        "        smlal v0.8h, v6.8b, v25.8b \n"
        "        smlal v1.8h, v7.8b, v25.8b \n"
        
        "        sadalp v12.4s, v0.8h       \n"
        "        sadalp v13.4s, v1.8h       \n"
        
        "        subs w17, w17, #2          \n"
        "        bne m2_loopkd8_nd2_even    \n"
        
        "    m2_loopkd8_nd2_end:            \n"
        "        addp v8.4s, v8.4s, v9.4s   \n"
        "        addp v12.4s, v12.4s, v13.4s\n"
        
        "        addp v8.4s, v8.4s, v8.4s   \n"
        "        addp v12.4s, v12.4s, v12.4s\n"
        
        "        // start process kd4 kd2 kd1 cases\n"
        "    m2_loopkd4_nd2:                \n"
        "        cmp %w6, #0                \n"
        "        beq m2_loopkd2_nd2         \n"
        "        // start subkernel_m2n2k4  \n"
        "        ld1 {v4.8b}, [%1], #8  // load B4x2\n"
        "        sxtl v4.8h, v4.8b          \n"
        "        mov v6.d[0], v4.d[1]       \n"
        
        "        ld1 {v2.8b}, [%0], #8  // load first A2x4\n"
        "        sxtl v2.8h, v2.8b          \n"
        "        mov v3.d[0], v2.d[1]       \n"
        
        "        smull v9.4s, v2.4h, v4.4h  \n"
        "        smull v10.4s, v2.4h, v6.4h \n"
        
        "        addp v9.4s, v9.4s, v10.4s  \n"
        "        addp v9.4s, v9.4s, v9.4s   \n"
        "        add v8.4s, v8.4s, v9.4s    \n"
        
        "        smull v13.4s, v3.4h, v4.4h \n"
        "        smull v14.4s, v3.4h, v6.4h \n"
        
        "        addp v13.4s, v13.4s, v14.4s\n"
        "        addp v13.4s, v13.4s, v13.4s\n"
        "        add v12.4s, v12.4s, v13.4s \n"
        
        "    m2_loopkd2_nd2:                \n"
        "        cmp %w7, 0                 \n"
        "        beq m2_loopkd1_nd2         \n"
        "        // start subkernel_m2n2k2  \n"
        "        ld1 {v4.8b}, [%0]   // load A2x2\n"
        "        add %0, %0, #4             \n"
        "        ld1 {v0.8b}, [%1]   // load B2x2\n"
        "        add %1, %1, #4             \n"
        "                            // 00 11\n"
        "        rev32 v1.4h, v0.4h  // 11 00\n"
        
        "        smull v21.8h, v4.8b, v0.8b \n"
        "        smull v22.8h, v4.8b, v1.8b \n"
        
        "        saddlp v21.4s, v21.8h      \n"
        "        saddlp v22.4s, v22.8h      \n"
        
        "        mov v9.s[0], v21.s[0]      \n"
        "        mov v9.s[1], v22.s[0]      \n"
        "        add v8.4s, v8.4s, v9.4s    \n"
        
        "        mov v13.s[0], v22.s[1]     \n"
        "        mov v13.s[1], v21.s[1]     \n"
        "        add v12.4s, v12.4s, v13.4s \n"
        
        "    m2_loopkd1_nd2:                \n"
        "        cmp %w8, #0                \n"
        "        beq m2_loopnd2_end         \n"
        "        // start subkernel_m2n2k1  \n"
        "        ld1 {v4.8b}, [%1]   // load B1x2\n"
        "        add %1, %1, #2             \n"
        "        ld1 {v2.8b}, [%0]   // load A4x1\n"
        "        add %0, %0, #2             \n"
        "        sxtl v4.8h, v4.8b          \n"
        "        sxtl v2.8h, v2.8b          \n"
        "        smlal v8.4s, v4.4h, v2.h[0]\n"
        "        smlal v12.4s, v4.4h, v2.h[1]   \n"
        
        "    m2_loopnd2_end:               \n"
        "        cmp %9, #0                \n"
        "        beq m2_loopnd2_write      \n"

        "        mov v8.d[1], v12.d[0]     \n"
        
        "        // v12: 0 1                \n"
        "        ld1 {v12.2s}, [%9]         \n"
        "        zip1 v12.4s, v12.4s, v12.4s\n"
        "        // v12: 0 0 1 1            \n"
        
        "        // int32 => fp32           \n"
        "        scvtf v8.4s, v8.4s         \n"
        "        // fp32 *= scale_tm        \n"
        "        fmul v8.4s, v8.4s, v12.4s  \n"
        
        "        cmp %10, #0                \n"
        "        beq m2_loopnd2_end_requant \n"
        
        "        // fp32 += bias_tm         \n"
        "        ld1 {v12.2s}, [%10]        \n"
        "        zip1 v12.4s, v12.4s, v12.4s\n"
        "        fadd v8.4s, v8.4s, v12.4s  \n"
        
        "        m2_loopnd2_end_requant:    \n"
        "            // fp32 -> int32       \n"
        "            fcvtas v8.4s, v8.4s    \n"
        "            // int32 -> int16      \n"
        "            sqxtn v8.4h, v8.4s     \n"
        "            // int16 -> int8       \n"
        "            sqxtn v8.8b, v8.8h     \n"
        "            // save                \n"
        "            st1 {v8.h}[0], [%2]    \n"
        "            add x10, x10, #2       \n"
        "            st1 {v8.h}[1], [%3]    \n"
        "            add x11, x11, #2       \n"
        "            b m2_loopnd2_finish    \n"

        "    m2_loopnd2_write:"
        "        st1 {v8.2s}, [%2], #8      \n"
        "        st1 {v12.2s}, [%3], #8     \n"
        "    m2_loopnd2_finish:             \n"
        "        mov %0, x8                 \n"
        : "=r"(pa),     // %0
          "=r"(pb),     // %1
          "=r"(pc0),    // %2
          "=r"(pc1),    // %3
          "=r"(k8_even),// %4 
          "=r"(k8),     // %5
          "=r"(k4),     // %6
          "=r"(k2),     // %7
          "=r"(k1),     // %8
          "=r"(scales), // %9
          "=r"(bias)    // %10
        : "0"(pa),
          "1"(pb),
          "2"(pc0),
          "3"(pc1),
          "4"(k8_even),
          "5"(k8),
          "6"(k4),
          "7"(k2),
          "8"(k1),
          "9"(scales),
          "10"(bias)
        : "cc", "memory", "x8", "w17", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"
        );
    }

    if (n1 > 0) {
        asm volatile(
        "eor v8.16b, v8.16b, v8.16b     \n"
        "eor v9.16b, v9.16b, v9.16b     \n"
        "eor v10.16b, v10.16b, v10.16b  \n"
        "eor v11.16b, v11.16b, v11.16b  \n"
        "eor v12.16b, v12.16b, v12.16b  \n"
        "eor v13.16b, v13.16b, v13.16b  \n"
        "eor v14.16b, v14.16b, v14.16b  \n"
        "eor v15.16b, v15.16b, v15.16b  \n"

        "eor v16.16b, v16.16b, v16.16b  \n"
        "eor v17.16b, v17.16b, v17.16b  \n"
        "eor v18.16b, v18.16b, v18.16b  \n"
        "eor v19.16b, v19.16b, v19.16b  \n"
        "eor v20.16b, v20.16b, v20.16b  \n"
        "eor v21.16b, v21.16b, v21.16b  \n"
        "eor v22.16b, v22.16b, v22.16b  \n"
        "eor v23.16b, v23.16b, v23.16b  \n"

        "m2_nd1_start:                  \n"
        "    cmp %w5, #0                \n"
        "    beq m2_loopkd4_nd1 // k <=7\n"
        
        "    mov w17, %w5\n"

        "    cmp %w4, #0 \n"
        "    beq m2_loopkd8_nd1_even // loop number is even \n"
        
        "    // start loopkd8_nd1   \n"
        "    subs w17, w17, #1      \n"
        "    ld1 {v4.8b}, [%1], #8  // load four lines of B\n"
        "    ld1 {v2.8b, v3.8b}, [%0], #16  // load two lines of PanelA\n"
        "    smull v0.8h, v4.8b, v2.8b  \n"
        "    smull v1.8h, v4.8b, v3.8b  \n"
        "    saddlp v8.4s, v0.8h        \n"
        "    saddlp v12.4s, v1.8h       \n"
        
        "    cmp w17, #0           \n"
        "    beq m2_loopkd8_nd1_end\n"
        
        "    m2_loopkd8_nd1_even:  \n"
        "        ld1 {v4.8b, v5.8b}, [%1], #16                  \n"
        "        ld1 {v24.8b, v25.8b, v26.8b, v27.8b}, [%0], #32\n"

        "        smull v0.8h, v24.8b, v4.8b \n"
        "        smlal v0.8h, v26.8b, v5.8b \n"
        "        sadalp v8.4s, v0.8h        \n"
        
        "        smull v1.8h, v25.8b, v4.8b \n"
        "        smlal v1.8h, v27.8b, v5.8b \n"
        "        sadalp v12.4s, v1.8h       \n"

        "        subs w17, w17, #2          \n"
        "        bne m2_loopkd8_nd1_even    \n"
        
        "    m2_loopkd8_nd1_end:            \n"
        "        addp v8.4s, v8.4s, v8.4s   \n"
        "        addp v8.4s, v8.4s, v8.4s   \n"
        "        addp v12.4s, v12.4s, v12.4s\n"
        "        addp v12.4s, v12.4s, v12.4s\n"
        
        "        // start process kd4 kd2 kd1 cases\n"
        "    m2_loopkd4_nd1:                       \n"
        "        cmp %w6, #0                       \n"
        "        beq m2_loopkd2_nd1                \n"
        "        // start subkernel_m2n1k2      \n"
        "        ld1 {v4.8b}, [%1]  // load B4x1\n"
        "        add %1, %1, #4                 \n"
        "        sxtl v4.8h, v4.8b   // extend B4x1 to v4\n"
        
        "        ld1 {v2.8b}, [%0], #8  // load A2x4    \n"
        "        sxtl v2.8h, v2.8b      \n"
        "        mov v5.d[0], v2.d[1]   \n"
        
        "        smull v9.4s, v2.4h, v4.4h  \n"
        "        addp v9.4s, v9.4s, v9.4s   \n"
        "        addp v9.4s, v9.4s, v9.4s   \n"
        "        add v8.4s, v8.4s, v9.4s    \n"
        
        "        smull v13.4s, v5.4h, v4.4h \n"
        "        addp v13.4s, v13.4s, v13.4s\n"
        "        addp v13.4s, v13.4s, v13.4s\n"
        "        add v12.4s, v12.4s, v13.4s \n"
        
        "    m2_loopkd2_nd1:                \n"
        "        cmp %w7, 0                 \n"
        "        beq m2_loopkd1_nd1         \n"
        "        // start subkernel_m2n1k2  \n"
        "        ld1 {v4.8b}, [%0]   // load A2x2\n"
        "        add %0, %0, #4             \n"
        "        ld1 {v0.8b}, [%1]   // load B2x1\n"
        "        add %1, %1, #2             \n"
        
        "        mov v0.h[1], v0.h[0]   \n"
        
        "        smull v0.8h, v0.8b, v4.8b  \n"
        "        saddlp v0.4s, v0.8h        \n"

        "        mov v9.s[0], v0.s[0]       \n"
        "        add v8.4s, v8.4s, v9.4s    \n"
        "        mov v13.s[0], v0.s[1]      \n"
        "        add v12.4s, v12.4s, v13.4s \n"
        
        "    m2_loopkd1_nd1:                \n"
        "        cmp %w8, 0                 \n"
        "        beq m2_loopnd1_end         \n"
        "        // start subkernel_m2n1k1  \n"
        
        "        ld1 {v0.8b}, [%1]    // load B1x1\n"
        "        add %1, %1, #1 \n"
        
        "        ld1 {v1.8b}, [%0]   // load A2x1\n"
        "        add %0, %0, #2 \n"

        "        sxtl v1.8h, v1.8b  \n"
        "        sxtl v0.8h, v0.8b  \n"
        
        "        smull v0.4s, v1.4h, v0.h[0]\n"
        "        mov v1.s[0], v0.s[1]       \n"

        "        add v8.4s, v8.4s, v0.4s    \n"
        "        add v12.4s, v12.4s, v1.4s  \n"
        
        "    m2_loopnd1_end:                \n"
        "        cmp %w9, #0                \n"
        "        beq m2_loopnd1_write       \n"
        "        mov v8.s[1], v12.s[0]      \n"
        
        "        // v12: s0 s1              \n"
        "        ld1 {v12.2s}, [%9]         \n"
        "        // int32 => fp32           \n"
        "        scvtf v8.2s, v8.2s         \n"
        "        // fp32 *= scale_tm        \n"
        "        fmul v8.2s, v8.2s, v12.2s  \n"
        
        "        cmp %10, #0 \n"
        "        beq m2_loopnd1_end_requant \n"
        
        "        // fp32 += bias_tm         \n"
        "        ld1 {v12.2s}, [%10]        \n"
        "        fadd v8.2s, v8.2s, v12.2s  \n"
        
        "        m2_loopnd1_end_requant:       \n"
        "            // fp32 -> int32       \n"
        "            fcvtas v8.2s, v8.2s    \n"
        "            // int32 -> int16      \n"
        "            sqxtn v8.4h, v8.4s     \n"
        "            // int16 -> int8       \n"
        "            sqxtn v8.8b, v8.8h     \n"
        "            // save                \n"
        "            st1 {v8.b}[0], [%2]    \n"
        "            st1 {v8.b}[1], [%3]    \n"
        "            b m2_finish            \n"

        "    m2_loopnd1_write:          \n"
        "        st1 {v8.s}[0], [%2]    \n"
        "        st1 {v12.s}[0], [%3]   \n"
        "    m2_finish:                 \n"
        "        mov x0, #0             \n"
        : "=r"(pa),     // %0
          "=r"(pb),     // %1
          "=r"(pc0),    // %2
          "=r"(pc1),    // %3
          "=r"(k8_even),// %4 
          "=r"(k8),     // %5
          "=r"(k4),     // %6
          "=r"(k2),     // %7
          "=r"(k1),     // %8
          "=r"(scales), // %9
          "=r"(bias)    // %10
        : "0"(pa),
          "1"(pb),
          "2"(pc0),
          "3"(pc1),
          "4"(k8_even),
          "5"(k8),
          "6"(k4),
          "7"(k2),
          "8"(k1),
          "9"(scales),
          "10"(bias)
        : "cc", "memory", "x8", "w17", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"
        );
    
    }

}

void int8kernel_m4_new(int32_t* dst, int8_t* sa, int8_t* sb, int m, int k, int n, int ldc) {
    int32_t *pc = dst;
    int8_t *pa = sa;
    int8_t *pb = sb;

    float* scales = nullptr;
    float* bias = nullptr;


    DECOMPOSE_K
    DECOMPOSE_N

    fprintf(stdout, "k8_e \tk8 \tk4 \tk2 \tk1 \tn4 \t n2 \tn1\n");
    fprintf(stdout, "%d \t%d \t%d \t%d \t%d \t%d \t%d \t%d\n", k8_even, k8, k4, k2, k1, n4, n2, n1);

    int32_t *pc0 = dst;
    int32_t *pc1 = pc0 + ldc;
    int32_t *pc2 = pc1 + ldc;
    int32_t *pc3 = pc2 + ldc;

    if (n4 > 0) {
        fprintf(stdout, "start m4n4 \n");
        asm volatile(
        "m4_loopnd4:                   \n"
        "   eor v8.8b, v8.8b, v8.8b    \n"
        "   eor v9.8b, v9.8b, v9.8b    \n"
        "   eor v10.8b, v10.8b, v10.8b \n"
        "   eor v11.8b, v11.8b, v11.8b \n"
        "   eor v12.8b, v12.8b, v12.8b \n"
        "   eor v13.8b, v13.8b, v13.8b \n"
        "   eor v14.8b, v14.8b, v14.8b \n"
        "   eor v15.8b, v15.8b, v15.8b \n"

        "   eor v16.8b, v16.8b, v16.8b \n"
        "   eor v17.8b, v17.8b, v17.8b \n"
        "   eor v18.8b, v18.8b, v18.8b \n"
        "   eor v19.8b, v19.8b, v19.8b \n"
        "   eor v20.8b, v20.8b, v20.8b \n"
        "   eor v21.8b, v21.8b, v21.8b \n"
        "   eor v22.8b, v22.8b, v22.8b \n"
        "   eor v23.8b, v23.8b, v23.8b \n"

        "   mov x8, %0          \n"
        "   cmp %w7, #0         \n"
        "   beq m4_loopkd4_nd4  \n"
        "   mov w20, %w7        \n"

        "   cmp %w6, #0         \n"
        "   beq m4_loopkd8_nd4_even\n"
        
        "   subs w20, w20, #1   \n"
        "   ld1 {v4.8b, v5.8b, v6.8b, v7.8b}, [%1], #32 \n"
        "   ld1 {v2.8b, v3.8b}, [%0], #16               \n"
        "   smull v0.8h, v4.8b, v2.8b                   \n"
        "   smull v1.8h, v4.8b, v3.8b                   \n"
       
        "   saddlp v8.4s, v0.8h             \n"
        "   saddlp v12.4s, v1.8h            \n"
        "   smull v0.8h, v5.8b, v2.8b       \n"
        "   smull v1.8h, v5.8b, v3.8b       \n"
        "   saddlp v9.4s, v0.8h             \n"
        "   saddlp v13.4s, v1.8h            \n"
        "   smull v0.8h, v6.8b, v2.8b       \n"
        "   smull v1.8h, v6.8b, v3.8b       \n"
        "   saddlp v10.4s, v0.8h            \n"
        "   saddlp v14.4s, v1.8h            \n"
        "   smull v0.8h, v7.8b, v2.8b       \n"
        "   smull v1.8h, v7.8b, v3.8b       \n"
        "   saddlp v11.4s, v0.8h            \n"
        "   ld1 {v2.8b, v3.8b}, [%0], #16   \n"
        "   saddlp v15.4s, v1.8h        \n"
        "   smull v0.8h, v4.8b, v2.8b   \n"
        "   smull v1.8h, v4.8b, v3.8b   \n"
        "   saddlp v16.4s, v0.8h        \n"
        "   saddlp v20.4s, v1.8h        \n"
        "   smull v0.8h, v5.8b, v2.8b   \n"
        "   smull v1.8h, v5.8b, v3.8b   \n"
        "   saddlp v17.4s, v0.8h        \n"
        "   saddlp v21.4s, v1.8h        \n"
        "   smull v0.8h, v6.8b, v2.8b   \n"
        "   smull v1.8h, v6.8b, v3.8b   \n"
        "   saddlp v18.4s, v0.8h        \n"
        "   saddlp v22.4s, v1.8h        \n"
        "   smull v0.8h, v7.8b, v2.8b   \n"
        "   smull v1.8h, v7.8b, v3.8b   \n"
        "   saddlp v19.4s, v0.8h        \n"
        "   saddlp v23.4s, v1.8h        \n"
       
        "   cmp w20, #0                 \n"
        "   beq m4_loopkd8_nd4_end      \n"
       
        "   m4_loopkd8_nd4_even:       \n"
        "       add x15, %x1, #32    \n"
        "       add x14, %x0, #32    \n"
        "       ld1 {v4.8b, v5.8b}, [%1], #16\n"
        "       ld1 {v2.8b, v3.8b}, [%0], #16\n"
       
        "       smull v0.8h, v4.8b, v2.8b       \n"
        "       ld1 {v6.8b, v7.8b}, [x15], #16  \n"
        "       smull v1.8h, v5.8b, v2.8b       \n"
        "       ld1 {v24.8b, v25.8b}, [x14], #16\n"
       
        "       smlal v0.8h, v6.8b, v24.8b\n"
        "       smlal v1.8h, v7.8b, v24.8b\n"
       
        "       sadalp v8.4s, v0.8h\n"
        "       sadalp v9.4s, v1.8h\n"

        "       smull v0.8h, v4.8b, v3.8b   \n"
        "       smull v1.8h, v5.8b, v3.8b   \n"
        "       smlal v0.8h, v6.8b, v25.8b  \n"
        "       smlal v1.8h, v7.8b, v25.8b  \n"
       
        "       sadalp v12.4s, v0.8h\n"
        "       sadalp v13.4s, v1.8h\n"
       
        "       // finish v8v9 v12v13, start proc v16v17,v20v21\n"
        "       ld1 {v28.8b, v29.8b}, [%0], #16 \n"
        "       smull v0.8h, v4.8b, v28.8b      \n"
        "       smull v1.8h, v5.8b, v28.8b      \n"
        "       ld1 {v26.8b, v27.8b}, [x14], #16\n"
        "       smlal v0.8h, v6.8b, v26.8b      \n"
        "       smlal v1.8h, v7.8b, v26.8b      \n"
        "       sadalp v16.4s, v0.8h            \n"
        "       sadalp v17.4s, v1.8h            \n"
       
        "       smull v0.8h, v4.8b, v29.8b  \n"
        "       smull v1.8h, v5.8b, v29.8b  \n"
        "       smlal v0.8h, v6.8b, v27.8b  \n"
        "       smlal v1.8h, v7.8b, v27.8b  \n"
        "       sadalp v20.4s, v0.8h        \n"
        "       sadalp v21.4s, v1.8h        \n"
       
        "       // start v10v11, v14v15, v18v19, v22v23\n"
        "       ld1 {v4.8b, v5.8b}, [%1], #16   \n"
        "       smull v0.8h, v4.8b, v2.8b       \n"
        "       smull v1.8h, v5.8b, v2.8b       \n"
        "       ld1 {v6.8b, v7.8b}, [x15], #16  \n"
        "       smlal v0.8h, v6.8b, v24.8b      \n"
        "       smlal v1.8h, v7.8b, v24.8b      \n"
        "       sadalp v10.4s, v0.8h            \n"
        "       sadalp v11.4s, v1.8h            \n"
       
        "       smull v0.8h, v4.8b, v3.8b   \n"
        "       smull v1.8h, v5.8b, v3.8b   \n"
        "       smlal v0.8h, v6.8b, v25.8b  \n"
        "       smlal v1.8h, v7.8b, v25.8b  \n"
        "       sadalp v14.4s, v0.8h        \n"
        "       sadalp v15.4s, v1.8h        \n"
       
        "       smull v0.8h, v4.8b, v28.8b  \n"
        "       smull v1.8h, v5.8b, v28.8b  \n"
        "       smlal v0.8h, v6.8b, v26.8b  \n"
        "       smlal v1.8h, v7.8b, v26.8b  \n"
        "       sadalp v18.4s, v0.8h        \n"
        "       sadalp v19.4s, v1.8h        \n"
    
        "       smull v0.8h, v4.8b, v29.8b  \n"
        "       smull v1.8h, v5.8b, v29.8b  \n"
        "       smlal v0.8h, v6.8b, v27.8b  \n"
        "       smlal v1.8h, v7.8b, v27.8b  \n"
        "       sadalp v22.4s, v0.8h        \n"
        "       sadalp v23.4s, v1.8h        \n"
    
        "       add %0, %0, #32     \n"
        "       add %1, %1, #32     \n"
        "       subs w20, w20, #2   \n"
        "       bne m4_loopkd8_nd4_even\n"
        // start nd2
        "    m4_loopkd8_nd4_end:               \n"
        "        addp v8.4s, v8.4s, v9.4s   \n"
        "        addp v10.4s, v10.4s, v11.4s\n"
        "        addp v12.4s, v12.4s, v13.4s\n"
        "        addp v14.4s, v14.4s, v15.4s\n"
        "        addp v16.4s, v16.4s, v17.4s\n"
        "        addp v18.4s, v18.4s, v19.4s\n"
        "        addp v20.4s, v20.4s, v21.4s\n"
        "        addp v22.4s, v22.4s, v23.4s\n"

        "        addp v8.4s, v8.4s, v10.4s  \n"
        "        addp v9.4s, v12.4s, v14.4s \n"
        "        addp v10.4s, v16.4s, v18.4s\n"
        "        addp v11.4s, v20.4s, v22.4s\n"

        "        // start process kd4 kd2 kd1 cases\n"
        "    m4_loopkd4_nd4:       \n"
        "        cmp %w8, #0     \n"
        "        beq m4_loopkd2_nd4\n"
        "        // start subkernel_m4n4k4\n"
        "        ld1 {v4.8b, v5.8b}, [%1], #16  // load B4x4\n"
        "        sxtl v4.8h, v4.8b      \n"
        "        mov v6.d[0], v4.d[1]   \n"
        "        sxtl v5.8h, v5.8b      \n"
        "        mov v7.d[0], v5.d[1]   \n"

        "        ld1 {v2.8b}, [%0], #8  // load A2x4\n"
        "        sxtl v2.8h, v2.8b      \n"
        "        mov v3.d[0], v2.d[1]   \n"

        "        smull v12.4s, v2.4h, v4.4h \n"
        "        smull v13.4s, v2.4h, v6.4h \n"
        "        smull v14.4s, v2.4h, v5.4h \n"
        "        addp v12.4s, v12.4s, v13.4s\n"
        "        smull v15.4s, v2.4h, v7.4h \n"

        "        addp v14.4s, v14.4s, v15.4s\n"
        "        addp v12.4s, v12.4s, v14.4s\n"

        "        smull v16.4s, v3.4h, v4.4h \n"
        "        add v8.4s, v8.4s, v12.4s   \n"

        "        smull v17.4s, v3.4h, v6.4h \n"
        "        smull v18.4s, v3.4h, v5.4h \n"
        "        addp v16.4s, v16.4s, v17.4s\n"
        "        smull v19.4s, v3.4h, v7.4h \n"
        "        addp v18.4s, v18.4s, v19.4s\n"
        "        addp v16.4s, v16.4s, v18.4s\n"
        "        add v9.4s, v9.4s, v16.4s   \n"

        "        ld1 {v2.8b}, [%0], #8 // load next A2x4\n"
        "        sxtl v2.8h, v2.8b          \n"
        "        mov v3.d[0], v2.d[1]       \n"

        "        smull v12.4s, v2.4h, v4.4h \n"
        "        smull v13.4s, v2.4h, v6.4h \n"
        "        smull v14.4s, v2.4h, v5.4h \n"
        "        addp v12.4s, v12.4s, v13.4s\n"
        "        smull v15.4s, v2.4h, v7.4h \n"

        "        addp v14.4s, v14.4s, v15.4s\n"
        "        addp v12.4s, v12.4s, v14.4s\n"
        "        smull v16.4s, v3.4h, v4.4h \n"
        "        add v10.4s, v10.4s, v12.4s \n"
        
        "        smull v17.4s, v3.4h, v6.4h \n"
        "        smull v18.4s, v3.4h, v5.4h \n"
        "        addp v16.4s, v16.4s, v17.4s\n"
        "        smull v19.4s, v3.4h, v7.4h \n"
        
        "        addp v18.4s, v18.4s, v19.4s\n"
        "        addp v16.4s, v16.4s, v18.4s\n"
        "        add v11.4s, v11.4s, v16.4s \n"
        
        "    m4_loopkd2_nd4:                \n"
        "        cmp %w9, #0                \n"
        "        beq m4_loopkd1_nd4         \n"
        "        // start subkernel_m4n4k2  \n"
        "        ld1 {v0.8b}, [%1], #8   // load B2x4   \n"
        "                            // 00 11 22 33     \n"
        "        rev32 v1.4h, v0.4h  // 11 00 33 22     \n"
        "        rev64 v2.2s, v0.2s  // 22 33 00 11     \n"
        "        ld1 {v4.8b}, [%0], #8   // load A4x2   \n"
        "        rev64 v3.4h, v0.4h  // 33 22 11 00     \n"
        
        "        smull v12.8h, v4.8b, v0.8b \n"
        "        smull v13.8h, v4.8b, v1.8b \n"
        "        saddlp v12.4s, v12.8h      \n"
        "        smull v14.8h, v4.8b, v2.8b \n"
        "        saddlp v13.4s, v13.8h      \n"
        "        smull v15.8h, v4.8b, v3.8b \n"
        "        saddlp v14.4s, v14.8h      \n"
        "        saddlp v15.4s, v15.8h      \n"
        
        "        mov v16.s[0], v12.s[0] \n"
        "        mov v16.s[1], v13.s[0] \n"
        "        mov v16.s[2], v14.s[0] \n"
        "        mov v16.s[3], v15.s[0] \n"
        
        "        mov v17.s[0], v13.s[1] \n"
        "        mov v17.s[1], v12.s[1] \n"
        "        mov v17.s[2], v15.s[1] \n"
        "        mov v17.s[3], v14.s[1] \n"

        "        mov v18.s[0], v14.s[2] \n"
        "        mov v18.s[1], v15.s[2] \n"
        "        mov v18.s[2], v12.s[2] \n"
        "        mov v18.s[3], v13.s[2] \n"
        
        "        mov v19.s[0], v15.s[3] \n"
        "        mov v19.s[1], v14.s[3] \n"
        "        mov v19.s[2], v13.s[3] \n"
        "        mov v19.s[3], v12.s[3] \n"
        
        "        add v8.4s, v8.4s, v16.4s   \n"
        "        add v9.4s, v9.4s, v17.4s   \n"
        "        add v10.4s, v10.4s, v18.4s \n"
        "        add v11.4s, v11.4s, v19.4s \n"
        
        "    m4_loopkd1_nd4:            \n"
        "        cmp %w10, #0           \n"
        "        beq m4_loopnd4_end     \n"
        "        // start subkernel_m4n4k1\n"
        "        ld1 {v4.8b}, [%1]   // load B1x4\n"
        "        add %1, %1, #4     \n"
        "        ld1 {v2.8b}, [%0]   // load A4x1\n"
        "        add %0, %0, #4     \n"
        "        sxtl v4.8h, v4.8b  \n"
        "        sxtl v2.8h, v2.8b  \n"
        "        smlal v8.4s, v4.4h, v2.h[0]    \n"
        "        smlal v9.4s, v4.4h, v2.h[1]    \n"
        "        smlal v10.4s, v4.4h, v2.h[2]   \n"
        "        smlal v11.4s, v4.4h, v2.h[3]   \n"
        
        "    m4_loopnd4_end:                       \n"
        "        // we should use a better quantization scheme\n"
        "        cmp %12, #0               \n"
        "        beq m4_loopnd4_write      \n"

        "        ld1 {v12.4s}, [%12] \n"
        "        // int32 => fp32       \n"
        "        scvtf v8.4s, v8.4s     \n"
        "        scvtf v9.4s, v9.4s     \n"
        "        scvtf v10.4s, v10.4s   \n"
        "        scvtf v11.4s, v11.4s   \n"
        "        // fp32 *= scale_tm    \n"
        "        fmul v8.4s, v8.4s, v12.s[0]    \n"
        "        fmul v9.4s, v9.4s, v12.s[1]    \n"
        "        fmul v10.4s, v10.4s, v12.s[2]  \n"
        "        fmul v11.4s, v11.4s, v12.s[3]  \n"
        
        "        cmp %13, #0            \n"
        "        beq m4_loopnd4_end_requant\n"
        
        "        ld1 {v14.4s}, [%13]    \n"
        "        dup v15.4s, v14.s[0]   \n"
        "        fadd v8.4s, v8.4s, v15.4s  \n"
        "        dup v15.4s, v14.s[1]       \n"
        "        fadd v9.4s, v9.4s, v15.4s  \n"
        "        dup v15.4s, v14.s[2]       \n"
        "        fadd v10.4s, v10.4s, v15.4s\n"
        "        dup v15.4s, v14.s[3]       \n"
        "        fadd v11.4s, v11.4s, v15.4s\n"
        
        "        m4_loopnd4_end_requant:       \n"
        "            // fp32 -> int32       \n"
        "            fcvtas v8.4s, v8.4s    \n"
        "            fcvtas v9.4s, v9.4s    \n"
        "            fcvtas v10.4s, v10.4s  \n"
        "            fcvtas v11.4s, v11.4s  \n"
        "            // int32 -> int16      \n"
        "            sqxtn v6.4h, v8.4s     \n"
        "            sqxtn2 v6.8h, v9.4s    \n"
        "            sqxtn v7.4h, v10.4s    \n"
        "            sqxtn2 v7.8h, v11.4s   \n"
        "            // int16 -> int8       \n"
        "            sqxtn v8.8b, v6.8h     \n"
        "            sqxtn v9.8b, v7.8h     \n"
        "            // save                \n"
        "            st1 {v8.s}[0], [x10]   \n"
        "            add %x2, %x2, #4       \n"
        "            st1 {v8.s}[1], [x11]   \n"
        "            add %x3, %x3, #4       \n"
        "            st1 {v9.s}[0], [x12]   \n"
        "            add %x4, %x4, #4       \n"
        "            st1 {v9.s}[1], [x13]   \n"
        "            add %x5, %x5, #4       \n"
        "            b m4_loopnd4_finish    \n"

        "    m4_loopnd4_write:              \n"
        "        st1 {v8.4s}, [%x2], #16    \n"
        "        st1 {v9.4s}, [%x3], #16    \n"
        "        st1 {v10.4s}, [%x4], #16   \n"
        "        st1 {v11.4s}, [%x5], #16   \n"
        
        "    m4_loopnd4_finish:          \n"
        "        subs %x11, %x11, #1     \n"
        "        mov %x0, x8             \n"
        "        bne m4_loopnd4          \n"
        : "=r"(pa),     // %0
          "=r"(pb),     // %1
          "=r"(pc0),    // %2
          "=r"(pc1),    // %3
          "=r"(pc2),    // %4
          "=r"(pc3),    // %5
          "=r"(k8_even),// %6 
          "=r"(k8),     // %7
          "=r"(k4),     // %8
          "=r"(k2),     // %9
          "=r"(k1),     // %10
          "=r"(n4),     // %11
          "=r"(scales), // %12
          "=r"(bias)    // %13
        : "0"(pa),
          "1"(pb),
          "2"(pc0),
          "3"(pc1),
          "4"(pc2),
          "5"(pc3),
          "6"(k8_even),
          "7"(k8),     
          "8"(k4),     
          "9"(k2),     
          "10"(k1),    
          "11"(n4),    
          "12"(scales),
          "13"(bias)   
        : "cc", "memory", "x8", "w20", "x14", "x15", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"
        );
    }

    if (n2 > 0) {
        fprintf(stdout, "start m4n2 \n");
        asm volatile(
        "    eor v8.8b, v8.8b, v8.8b    \n"
        "    eor v9.8b, v9.8b, v9.8b    \n"
        "    eor v10.8b, v10.8b, v10.8b \n"
        "    eor v11.8b, v11.8b, v11.8b \n"
        "    eor v12.8b, v12.8b, v12.8b \n"
        "    eor v13.8b, v13.8b, v13.8b \n"
        "    eor v14.8b, v14.8b, v14.8b \n"
        "    eor v15.8b, v15.8b, v15.8b \n"

        "    eor v16.8b, v16.8b, v16.8b \n"
        "    eor v17.8b, v17.8b, v17.8b \n"
        "    eor v18.8b, v18.8b, v18.8b \n"
        "    eor v19.8b, v19.8b, v19.8b \n"
        "    eor v20.8b, v20.8b, v20.8b \n"
        "    eor v21.8b, v21.8b, v21.8b \n"
        "    eor v22.8b, v22.8b, v22.8b \n"
        "    eor v23.8b, v23.8b, v23.8b \n"

        "m4_nd2_start:                  \n"
        "    mov x8, %x0  // PanelA     \n"
        
        "    cmp %w7, #0                 \n"
        "    beq m4_loopkd4_nd2  // k <= 7     \n"
        
        "    mov w20, %w7                \n"
        "    cmp %w6, #0                 \n"
        "    beq m4_loopkd8_nd2_even  // loop number is even \n"
        
        "    // start loopkd8_nd2       \n"
        "    subs w20, w20, #1          \n"
        "    ld1 {v4.8b, v5.8b}, [%1], #16  // load two lines of B\n"
        "    ld1 {v2.8b, v3.8b}, [%0], #16  // load two lines of PanelA\n"
        "    smull v0.8h, v4.8b, v2.8b  \n"
        "    smull v1.8h, v4.8b, v3.8b  \n"
        "    saddlp v8.4s, v0.8h        \n"
        "    saddlp v12.4s, v1.8h       \n"
        "    smull v0.8h, v5.8b, v2.8b  \n"
        "    smull v1.8h, v5.8b, v3.8b  \n"
        "    saddlp v9.4s, v0.8h        \n"
        "    saddlp v13.4s, v1.8h       \n"
        
        "    ld1 {v2.8b, v3.8b}, [%0], #16  \n"
        "    smull v0.8h, v4.8b, v2.8b      \n"
        "    smull v1.8h, v4.8b, v3.8b      \n"
        "    saddlp v16.4s, v0.8h       \n"
        "    saddlp v20.4s, v1.8h       \n"
        "    smull v0.8h, v5.8b, v2.8b  \n"
        "    smull v1.8h, v5.8b, v3.8b  \n"
        "    saddlp v17.4s, v0.8h       \n"
        "    saddlp v21.4s, v1.8h       \n"
        
        "    cmp w20, #0                 \n"
        "    beq m4_loopkd8_nd2_end        \n"
        
        "    m4_loopkd8_nd2_even: \n"
        "        add x15, %1, #16 \n"
        "        add x14, %0, #32 \n"
        "        ld1 {v4.8b, v5.8b}, [%1], #16  \n"
        "        ld1 {v2.8b, v3.8b}, [%0], #16  \n"
        
        "        smull v0.8h, v4.8b, v2.8b      \n"
        "        ld1 {v6.8b, v7.8b}, [x15], #16 \n"
        "        smull v1.8h, v5.8b, v2.8b        \n"
        "        ld1 {v24.8b, v25.8b}, [x14], #16 \n"
        
        "        smlal v0.8h, v6.8b, v24.8b     \n"
        "        smlal v1.8h, v7.8b, v24.8b     \n"
        
        "        sadalp v8.4s, v0.8h    \n"
        "        sadalp v9.4s, v1.8h    \n"

        "        smull v0.8h, v4.8b, v3.8b  \n"
        "        smull v1.8h, v5.8b, v3.8b  \n"
        "        smlal v0.8h, v6.8b, v25.8b \n"
        "        smlal v1.8h, v7.8b, v25.8b \n"
        
        "        sadalp v12.4s, v0.8h   \n"
        "        sadalp v13.4s, v1.8h   \n"
        
        "        // finish v8v9 v12v13, start proc v16v17,v20v21\n"
        "        ld1 {v28.8b, v29.8b}, [%0], #16\n"
        "        smull v0.8h, v4.8b, v28.8b\n"
        "        smull v1.8h, v5.8b, v28.8b\n"
        "        ld1 {v26.8b, v27.8b}, [x14], #16\n"
        "        smlal v0.8h, v6.8b, v26.8b\n"
        "        smlal v1.8h, v7.8b, v26.8b\n"
        "        sadalp v16.4s, v0.8h\n"
        "        sadalp v17.4s, v1.8h\n"
        
        "        smull v0.8h, v4.8b, v29.8b\n"
        "        smull v1.8h, v5.8b, v29.8b\n"
        "        smlal v0.8h, v6.8b, v27.8b\n"
        "        smlal v1.8h, v7.8b, v27.8b\n"
        "        sadalp v20.4s, v0.8h\n"
        "        sadalp v21.4s, v1.8h\n"
        
        "        add %0, %0, #32        \n"
        "        add %1, %1, #16        \n"
        "        subs w20, w20, #2      \n"
        "        bne m4_loopkd8_nd2_even\n"
        
        "    m4_loopkd8_nd2_end:            \n"
        "        addp v8.4s, v8.4s, v9.4s   \n"
        "        addp v12.4s, v12.4s, v13.4s\n"
        "        addp v16.4s, v16.4s, v17.4s\n"
        "        addp v20.4s, v20.4s, v21.4s\n"
        
        "        addp v8.4s, v8.4s, v8.4s   \n"
        "        addp v12.4s, v12.4s, v12.4s\n"
        "        addp v16.4s, v16.4s, v16.4s\n"
        "        addp v20.4s, v20.4s, v20.4s\n"
        
        "        // start process kd4 kd2 kd1 cases\n"
        "    m4_loopkd4_nd2:   \n"
        "        cmp %w8, 0 \n"
        "        beq m4_loopkd2_nd2 \n"
        "        // start subkernel_m4n2k4  \n"
        "        ld1 {v4.8b}, [%1], #8  // load B4x2\n"
        "        sxtl v4.8h, v4.8b      \n"
        "        mov v6.d[0], v4.d[1]   \n"
        
        "        ld1 {v2.8b}, [%0], #8  // load first A2x4\n"
        "        sxtl v2.8h, v2.8b      \n"
        "        mov v3.d[0], v2.d[1]   \n"
        
        "        smull v9.4s, v2.4h, v4.4h  \n"
        "        smull v10.4s, v2.4h, v6.4h \n"
        
        "        addp v9.4s, v9.4s, v10.4s  \n"
        "        addp v9.4s, v9.4s, v9.4s   \n"
        "        add v8.4s, v8.4s, v9.4s    \n"
        
        "        smull v13.4s, v3.4h, v4.4h \n"
        "        smull v14.4s, v3.4h, v6.4h \n"
        
        "        addp v13.4s, v13.4s, v14.4s\n"
        "        addp v13.4s, v13.4s, v13.4s\n"
        "        add v12.4s, v12.4s, v13.4s \n"
        
        "        ld1 {v2.8b}, [%0], #8 // load next A2x4\n"
        "        sxtl v2.8h, v2.8b          \n"
        "        mov v3.d[0], v2.d[1]       \n"
        
        "        smull v17.4s, v2.4h, v4.4h \n"
        "        smull v18.4s, v2.4h, v6.4h \n"
        
        "        addp v17.4s, v17.4s, v18.4s\n"
        "        addp v17.4s, v17.4s, v17.4s\n"
        "        add v16.4s, v16.4s, v17.4s \n"
        
        "        smull v21.4s, v3.4h, v4.4h \n"
        "        smull v22.4s, v3.4h, v6.4h \n"
        
        "        addp v21.4s, v21.4s, v22.4s\n"
        "        addp v21.4s, v21.4s, v21.4s\n"
        "        add v20.4s, v20.4s, v21.4s \n"
        
        "    m4_loopkd2_nd2:                \n"
        "        cmp %w9, 0                  \n"
        "        beq m4_loopkd1_nd2         \n"
        "        // start subkernel_m4n2k2  \n"
        "        ld1 {v4.8b}, [%0], #8   //load A4x2\n"
        "        ld1 {v0.8b}, [%1]   // load B2x2   \n"
        "        add %1, %1, #4                     \n"
        "                            // 00 11 22 33 \n"
        "        rev32 v1.4h, v0.4h  // 11 00 33 22 \n"
        "        rev64 v2.2s, v0.2s  // 22 33 00 11 \n"
        "        rev64 v3.4h, v0.4h  // 33 22 11 00 \n"
        
        "        smull v21.8h, v4.8b, v0.8b \n"
        "        smull v22.8h, v4.8b, v1.8b \n"
        "        smull v23.8h, v4.8b, v2.8b \n"
        "        smull v24.8h, v4.8b, v3.8b \n"
        
        "        saddlp v21.4s, v21.8h  \n"
        "        saddlp v22.4s, v22.8h  \n"
        "        saddlp v23.4s, v23.8h  \n"
        "        saddlp v24.4s, v24.8h  \n"
        
        "        mov v9.s[0], v21.s[0]  \n"
        "        mov v9.s[1], v22.s[0]  \n"
        "        add v8.4s, v8.4s, v9.4s\n"
        
        "        mov v13.s[0], v22.s[1] \n"
        "        mov v13.s[1], v21.s[1] \n"
        "        add v12.4s, v12.4s, v13.4s \n"
        
        "        mov v17.s[0], v23.s[2] \n"
        "        mov v17.s[1], v24.s[2] \n"
        "        add v16.4s, v16.4s, v17.4s \n"
        
        "        mov v21.s[0], v24.s[3]     \n"
        "        mov v21.s[1], v23.s[3]     \n"
        "        add v20.4s, v20.4s, v21.4s \n"
        
        "    m4_loopkd1_nd2:   \n"
        "        cmp %w10, 0    \n"
        "        beq m4_loopnd2_end    \n"
        "        // start subkernel_m4n2k1\n"
        "        ld1 {v4.8b}, [%1]   // load B1x2\n"
        "        add %1, %1, #2     \n"
        "        ld1 {v2.8b}, [%0]   // load A4x1\n"
        "        add %0, %0, #4     \n"
        "        sxtl v4.8h, v4.8b  \n"
        "        sxtl v2.8h, v2.8b  \n"
        "        smlal v8.4s, v4.4h, v2.h[0]    \n"
        "        smlal v12.4s, v4.4h, v2.h[1]   \n"
        "        smlal v16.4s, v4.4h, v2.h[2]   \n"
        "        smlal v20.4s, v4.4h, v2.h[3]   \n"
        
        "    m4_loopnd2_end:               \n"
        "        cmp %11, #0               \n"
        "        beq m4_loopnd2_write      \n"

        "        mov v8.d[1], v12.d[0]  \n"
        "        mov v16.d[1], v20.d[0] \n"
        
        "        // v12: 0 1 2 3        \n"
        "        ld1 {v12.4s}, [%11]     \n"
        "        zip2 v13.4s, v12.4s, v12.4s    \n"
        "        zip1 v12.4s, v12.4s, v12.4s    \n"
        "        // v12: 0 0 1 1        \n"
        "        // v13: 2 2 3 3        \n"
        
        "        // int32 => fp32   \n"
        "        scvtf v8.4s, v8.4s \n"
        "        scvtf v16.4s, v16.4s   \n"
        "        // fp32 *= scale_tm    \n"
        "        fmul v8.4s, v8.4s, v12.4s  \n"
        "        fmul v16.4s, v16.4s, v13.4s\n"
        
        "        cmp %12, #0   \n"
        "        beq m4_loopnd2_end_requant   // skip add scales\n"
        
        "        // fp32 += scales_tm       \n"
        "        ld1 {v12.4s}, [%12]         \n"
        "        zip2 v13.4s, v12.4s, v12.4s\n"
        "        zip1 v12.4s, v12.4s, v12.4s\n"
        "        fadd v8.4s, v8.4s, v12.4s  \n"
        "        fadd v16.4s, v16.4s, v13.4s\n"
        
        "        m4_loopnd2_end_requant:       \n"
        "            // fp32 -> int32       \n"
        "            fcvtas v8.4s, v8.4s    \n"
        "            fcvtas v16.4s, v16.4s  \n"
        "            // int32 -> int16      \n"
        "            sqxtn v8.4h, v8.4s     \n"
        "            sqxtn v16.4h, v16.4s   \n"
        "            // int16 -> int8       \n"
        "            sqxtn v8.8b, v8.8h     \n"
        "            sqxtn v16.8b, v16.8h   \n"
        "            // save                \n"
        "            st1 {v8.h}[0], [%2]    \n"
        "            add x10, x10, #2       \n"
        "            st1 {v8.h}[1], [%3]    \n"
        "            add x11, x11, #2       \n"
        "            st1 {v16.h}[0], [%4]   \n"
        "            add x12, x12, #2       \n"
        "            st1 {v16.h}[1], [%5]   \n"
        "            add x13, x13, #2       \n"
        "            b m4_loopnd2_finish    \n"

        "    m4_loopnd2_write:             \n"
        "        st1 {v8.2s}, [%2], #8     \n"
        "        st1 {v12.2s}, [%3], #8    \n"
        "        st1 {v16.2s}, [%4], #8    \n"
        "        st1 {v20.2s}, [%5], #8    \n"

        "    m4_loopnd2_finish:             \n"
        "        mov %0, x8                 \n"
        : "=r"(pa),     // %0
          "=r"(pb),     // %1
          "=r"(pc0),    // %2
          "=r"(pc1),    // %3
          "=r"(pc2),    // %4
          "=r"(pc3),    // %5
          "=r"(k8_even),// %6
          "=r"(k8),     // %7
          "=r"(k4),     // %8
          "=r"(k2),     // %9
          "=r"(k1),     // %10
          "=r"(scales), // %11
          "=r"(bias)    // %12
        : "0"(pa),
          "1"(pb),
          "2"(pc0),
          "3"(pc1),
          "4"(pc2),
          "5"(pc3),
          "6"(k8_even),
          "7"(k8),
          "8"(k4),
          "9"(k2),
          "10"(k1),
          "11"(scales),
          "12"(bias)
        : "cc", "memory", "x8", "w20", "x14", "x15", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"
        );
    }

    if (n1 > 0) {
        fprintf(stdout, "start m4n1 \n");
        asm volatile(
        "    eor v8.8b, v8.8b, v8.8b    \n"
        "    eor v9.8b, v9.8b, v9.8b    \n"
        "    eor v10.8b, v10.8b, v10.8b \n"
        "    eor v11.8b, v11.8b, v11.8b \n"
        "    eor v12.8b, v12.8b, v12.8b \n"
        "    eor v13.8b, v13.8b, v13.8b \n"
        "    eor v14.8b, v14.8b, v14.8b \n"
        "    eor v15.8b, v15.8b, v15.8b \n"

        "    eor v16.8b, v16.8b, v16.8b \n"
        "    eor v17.8b, v17.8b, v17.8b \n"
        "    eor v18.8b, v18.8b, v18.8b \n"
        "    eor v19.8b, v19.8b, v19.8b \n"
        "    eor v20.8b, v20.8b, v20.8b \n"
        "    eor v21.8b, v21.8b, v21.8b \n"
        "    eor v22.8b, v22.8b, v22.8b \n"
        "    eor v23.8b, v23.8b, v23.8b \n"

        "m4_n1_start:                       \n"
        "    cmp %w7, #0                     \n"
        "    beq m4_loopkd4_nd1 // k <= 7   \n"
        
        "    mov w20, %w7        \n"
        "    cmp %w6, #0         \n"
        "    beq m4_loopkd8_nd1_even // loop number is even \n"
        
        "    // start loopkd8_nd1       \n"
        "    subs w20, w20, #1          \n"
        "    ld1 {v4.8b}, [%1], #8  // load four lines of B\n"
        "    ld1 {v2.8b, v3.8b}, [%0], #16  // load two lines of PanelA\n"
        "    smull v0.8h, v4.8b, v2.8b  \n"
        "    smull v1.8h, v4.8b, v3.8b  \n"
        "    saddlp v8.4s, v0.8h        \n"
        "    saddlp v12.4s, v1.8h       \n"
        
        "    ld1 {v2.8b, v3.8b}, [%0], #16  \n"
        "    smull v0.8h, v4.8b, v2.8b  \n"
        "    smull v1.8h, v4.8b, v3.8b  \n"
        "    saddlp v16.4s, v0.8h       \n"
        "    saddlp v20.4s, v1.8h       \n"
        
        "    cmp w20, #0                \n"
        "    beq m4_loopkd8_nd1_end     \n"
        
        "    m4_loopkd8_nd1_even:          \n"
        "        ld1 {v4.8b, v5.8b}, [%1], #16  \n"
        "        ld1 {v24.8b, v25.8b, v26.8b, v27.8b}, [%0], #32\n"
        "        ld1 {v28.8b, v29.8b, v30.8b, v31.8b}, [%0], #32\n"

        "        smull v0.8h, v24.8b, v4.8b \n"
        "        smlal v0.8h, v28.8b, v5.8b \n"
        "        sadalp v8.4s, v0.8h        \n"
        
        "        smull v1.8h, v25.8b, v4.8b \n"
        "        smlal v1.8h, v29.8b, v5.8b \n"
        "        sadalp v12.4s, v1.8h       \n"

        "        smull v0.8h, v26.8b, v4.8b \n"
        "        smlal v0.8h, v30.8b, v5.8b \n"
        "        sadalp v16.4s, v0.8h       \n"
        
        "        smull v1.8h, v27.8b, v4.8b \n"
        "        smlal v1.8h, v31.8b, v5.8b \n"
        "        sadalp v20.4s, v1.8h       \n"
        
        "        subs w20, w20, #2            \n"
        "        bne m4_loopkd8_nd1_even       \n"
        
        "    m4_loopkd8_nd1_end:               \n"
        "        addp v8.4s, v8.4s, v8.4s   \n"
        "        addp v8.4s, v8.4s, v8.4s   \n"
        "        addp v12.4s, v12.4s, v12.4s\n"
        "        addp v12.4s, v12.4s, v12.4s\n"
        "        addp v16.4s, v16.4s, v16.4s\n"
        "        addp v16.4s, v16.4s, v16.4s\n"
        "        addp v20.4s, v20.4s, v20.4s\n"
        "        addp v20.4s, v20.4s, v20.4s\n"
        
        "        // start process kd4 kd2 kd1 cases\n"
        "    m4_loopkd4_nd1:           \n"
        "        cmp %w8, #0            \n"
        "        beq m4_loopkd2_nd1    \n"
        "        // start subkernel_m4n1k2      \n"
        "        ld1 {v4.8b}, [%1]  // load B4x1\n"
        "        add %x1, %x1, #4       \n"
        "        sxtl v4.8h, v4.8b   // extend B4x1 to v4   \n"
        
        "        ld1 {v2.8b, v3.8b}, [%0], #16  // load A4x4\n"
        "        sxtl v2.8h, v2.8b      \n"
        "        mov v5.d[0], v2.d[1]   \n"
        "        sxtl v3.8h, v3.8b      \n"
        "        mov v6.d[0], v3.d[1]  // extend A4x4 to v2,v5,v3,v6\n"
        
        "        smull v9.4s, v2.4h, v4.4h  \n"
        "        addp v9.4s, v9.4s, v9.4s   \n"
        "        addp v9.4s, v9.4s, v9.4s   \n"
        "        add v8.4s, v8.4s, v9.4s    \n"
        
        "        smull v13.4s, v5.4h, v4.4h \n"
        "        addp v13.4s, v13.4s, v13.4s\n"
        "        addp v13.4s, v13.4s, v13.4s\n"
        "        add v12.4s, v12.4s, v13.4s \n"
        
        "        smull v17.4s, v3.4h, v4.4h \n"
        "        addp v17.4s, v17.4s, v17.4s\n"
        "        addp v17.4s, v17.4s, v17.4s\n"
        "        add v16.4s, v16.4s, v17.4s \n"
        
        "        smull v21.4s, v6.4h, v4.4h \n"
        "        addp v21.4s, v21.4s, v21.4s\n"
        "        addp v21.4s, v21.4s, v21.4s\n"
        "        add v20.4s, v20.4s, v21.4s \n"
        
        "    m4_loopkd2_nd1:                \n"
        "        cmp %w9, #0                \n"
        "        beq m4_loopkd1_nd1         \n"
        "        // start subkernel_m4n1k2  \n"
        "        ld1 {v4.8b}, [%0], #8   // load A4x2   \n"
        "        ld1 {v0.8b}, [%1]   // load B2x1   \n"
        "        add %1, %1, #2             \n"
        
        "        mov v0.h[1], v0.h[0]   \n"
        "        mov v0.s[1], v0.s[0]   \n"
        
        "        smull v0.8h, v0.8b, v4.8b  \n"
        "        saddlp v0.4s, v0.8h        \n"

        "        mov v9.s[0], v0.s[0]       \n"
        "        add v8.4s, v8.4s, v9.4s    \n"
        "        mov v13.s[0], v0.s[1]      \n"
        "        add v12.4s, v12.4s, v13.4s \n"
        "        mov v17.s[0], v0.s[2]      \n"
        "        add v16.4s, v16.4s, v17.4s \n"
        "        mov v21.s[0], v0.s[3]      \n"
        "        add v20.4s, v20.4s, v21.4s \n"
        
        "    m4_loopkd1_nd1:                \n"
        "        cmp %w10, #0               \n"
        "        beq m4_loopnd1_end         \n"
        "        // start subkernel_m4n1k1  \n"
        #if 1 
        "        ld1 {v4.8b}, [%1]   // load B1x1\n"
        #else
        "        ldrb w3, [%1]              \n"
        "        dup v4.8b, w3              \n"
        #endif

        "        add %1, %1, #1             \n"
        "        ld1 {v2.8b}, [%0]   // load A4x1\n"
        "        add %0, %0, #4             \n"
        "        sxtl v4.8h, v4.8b          \n"
        "        sxtl v2.8h, v2.8b          \n"
        
        "        smull v0.4s, v2.4h, v4.h[0]\n"
        
        "        add v8.4s, v8.4s, v0.4s    \n"
        
        "        mov v13.s[0], v0.s[1]      \n"
        "        add v12.4s, v12.4s, v13.4s \n"
        
        "        mov v17.s[0], v0.s[2]      \n"
        "        add v16.4s, v16.4s, v17.4s \n"
        
        "        mov v21.s[0], v0.s[3]      \n"
        "        add v20.4s, v20.4s, v21.4s \n"
        
        "    m4_loopnd1_end:               \n"
        // REQUANT
        "        cmp %11, #0               \n"
        "        beq m4_loopnd1_write      \n"

        "        mov v8.s[1], v12.s[0]  \n"
        "        mov v8.s[2], v16.s[0]  \n"
        "        mov v8.s[3], v20.s[0]  \n"
        
        "        // v12: s0 s1 s2 s3    \n"
        "        ld1 {v12.4s}, [%11] \n"
        "        // int32 => fp32       \n"
        "        scvtf v8.4s, v8.4s     \n"
        "        // fp32 *= scale_tm    \n"
        "        fmul v8.4s, v8.4s, v12.4s  \n"
        
        "        cmp %12, #0                \n"
        "        beq m4_loopnd1_end_requant \n"
        
        "        // fp32 += bias_tm           \n"
        "        ld1 {v12.4s}, [%12]        \n"
        "        fadd v8.4s, v8.4s, v12.4s  \n"
        
        "        m4_loopnd1_end_requant:    \n"
        "            // fp32 -> int32       \n"
        "            fcvtas v8.4s, v8.4s    \n"
        "            // int32 -> int16      \n"
        "            sqxtn v8.4h, v8.4s     \n"
        "            // int16 -> int8       \n"
        "            sqxtn v8.8b, v8.8h     \n"
        "            // save                \n"
        "            st1 {v8.b}[0], [%2]   \n"
        "            st1 {v8.b}[1], [%3]   \n"
        "            st1 {v8.b}[2], [%4]   \n"
        "            st1 {v8.b}[3], [%5]   \n"
        "            b m4_finish            \n"

        "        // no need to add the last output pointer\n"
        "    m4_loopnd1_write:              \n"
        "        st1 {v8.s}[0], [%2]       \n"
        "        st1 {v12.s}[0], [%3]      \n"
        "        st1 {v16.s}[0], [%4]      \n"
        "        st1 {v20.s}[0], [%5]      \n"

        "    m4_finish:                     \n"
        "        mov x0, #0                 \n"
        : "=r"(pa),     // %0
          "=r"(pb),     // %1
          "=r"(pc0),    // %2
          "=r"(pc1),    // %3
          "=r"(pc2),    // %4
          "=r"(pc3),    // %5
          "=r"(k8_even),// %6
          "=r"(k8),     // %7
          "=r"(k4),     // %8
          "=r"(k2),     // %9
          "=r"(k1),     // %10
          "=r"(scales), // %11
          "=r"(bias)    // %12
        : "0"(pa),
          "1"(pb),
          "2"(pc0),
          "3"(pc1),
          "4"(pc2),
          "5"(pc3),
          "6"(k8_even),
          "7"(k8),
          "8"(k4),
          "9"(k2),
          "10"(k1),
          "11"(scales),
          "12"(bias)
        : "cc", "memory", "x0", "x8", "w20", "x14", "x15", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"
        );
    }

}
#undef DECOMPOSE_K
#undef DECOMPOSE_N

void print_int8_matrix(int8_t* data, int m, int n, int ldx)  {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            fprintf(stdout, "%d \t", data[i * ldx + j]);
        }
        fprintf(stdout, "\n");
    }
}

void print_int32_matrix(int32_t* data, int m, int n, int ldx)  {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            fprintf(stdout, "%d \t", data[i * ldx + j]);
        }
        fprintf(stdout, "\n");
    }
}

void int8kernel(int32_t* dst, int8_t* sa, int8_t* sb, int m, int k, int n, int ld, float* scales, float* bias) {
    int8_t* pa = sa;
    int8_t* pb = sb;
    int32_t* pc = dst;
    const int nn = (m >> 2) << 2;

    for (int i = 0; i < nn; i += 4) {
        int8kernel_m4_new(pc + i * n, pa + i * k, pb, m, k, n, n);
        fprintf(stdout, "end 1 m4_kernel\n");
    }

    pa += nn * k;
    pb += nn * n;

    switch(m-nn)
    {
        case 3:
            int8kernel_m2_new(pc, pa, pb, m, k, n, n);
            pc += 2 * n;
            pa += 2 * k;
            int8kernel_m1_new(pc, pa, pb, m, k, n, n);
            break;
        case 2:
            int8kernel_m2_new(pc, pa, pb, m, k, n, n);
            break;
        case 1:
            int8kernel_m1_new(pc, pa, pb, m, k, n, n);
            break;
        case 0:
        default:
            break;
    }
    return;
}

extern "C" {
    void int8kernel_m4(int32_t* dst, const int8_t* sa, const int8_t* sb, size_t k, size_t n, size_t ldc);
    void int8kernel_m2(int32_t* dst, const int8_t* sa, const int8_t* sb, size_t k, size_t n, size_t ldc);
    void int8kernel_m1(int32_t* dst, const int8_t* sa, const int8_t* sb, size_t k, size_t n, size_t ldc);
    void reorder_a(const int8_t *a, int8_t *sa, int m, int k, int ldx);
    void int8kernel_m4_requant(int8_t* dst, const int8_t* sa, const int8_t* sb, size_t k, size_t n, size_t ldc, float* scales, const float* bias);
    void int8kernel_m2_requant(int8_t* dst, const int8_t* sa, const int8_t* sb, size_t k, size_t n, size_t ldc, float* scales, const float* bias);
    void int8kernel_m1_requant(int8_t* dst, const int8_t* sa, const int8_t* sb, size_t k, size_t n, size_t ldc, float* scales, const float* bias);
}

void baseline(int8_t* pa, int8_t* pb, int32_t* pc, int m, int k, int n) {
#define A(i, j) (*(pa+(i)*k+j))
#define B(i, j) (*(pb+(i)*n+j))
#define C(i, j) (*(pc+(i)*n+j))
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int32_t sum = 0;
            for (int x = 0; x < k; x++) {
                sum += A(i, x) * B(x, j);
            }
            C(i, j) = sum;
        }
    }
#undef A
#undef B
#undef C
}

static inline void* fastMalloc(int size) {
    void* ptr = 0;
    int iRet = posix_memalign(&ptr, 64, size);
    assert(0 == iRet);
    return ptr;
}

int test(int m, int k, int n, int ldc) {
    fprintf(stdout, "\n---- begin test m: %d, k: %d, n: %d\n", m, k, n);
    int8_t* a     = (int8_t*)fastMalloc(2*m*k);    
    int8_t* sa    = (int8_t*)fastMalloc(2*m*k);    
    int8_t* sa_as = (int8_t*)fastMalloc(2*m*k);    

    int8_t* b  = (int8_t*)fastMalloc(2*k*n);
    int8_t* sb = (int8_t*)fastMalloc(2*k*n);

    int32_t* c  = (int32_t*)fastMalloc(2*m*n*sizeof(int32_t));
    int32_t* sc = (int32_t*)fastMalloc(2*m*n*sizeof(int32_t));

    for (int i = 0; i < m*n; ++i) {
        c[i] = sc[i] = 0;
    }

    int8_t val = 0;
    for (int i = 0; i < m*k; i++) {
        a[i] = val++;
    }
    fprintf(stdout, "----- print a:\n");
    print_int8_matrix(a, m, k, k);

    val = 0;
    for (int i = 0; i < k*n; i++) {
        b[i] = val++;
    }
    fprintf(stdout, "----- print b:\n");
    print_int8_matrix(b, k, n, n);

    
    reorder_a(a, sa, m, k, k);
    reorder_a_c(a, sa_as, m, k, k);

    fprintf(stdout, "** reorder_a finish\n");

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            int idx = i * k + j;
            if (sa[idx] != sa_as[idx]) {
                fprintf(stdout, " reorder_a err in [%d, %d]\n", i, j);    
                exit(-1);
            }
        }
    }

    reorder_b(b, sb, k, n, n);
    fprintf(stdout, "** reorder_b finish\n");

    {
        int8_t* pa = sa;
        int8_t* pb = sb;
        int32_t* pc = c;
        const int nn = (m >> 2) << 2;
        for (int i = 0; i < nn; i += 4) {
            int8kernel_m4(pc + i * ldc, pa + i * k, pb, k, n, n);
        }
        pa += nn * k;
        pb += nn * n;

        switch(m-nn)
        {
            case 3:
                int8kernel_m2(pc, pa, pb, k, n, n);
                pc += 2 * n;
                pa += 2 * k;
                int8kernel_m1(pc, pa, pb, k, n, n);
                break;
            case 2:
                int8kernel_m2(pc, pa, pb, k, n, n);
                break;
            case 1:
                int8kernel_m1(pc, pa, pb, k, n, n);
                break;
            case 0:
            default:
                break;
        }
    }
    fprintf(stdout, "----- print baseline:\n");
    print_int32_matrix(c, m, n, n);
//    fprintf(stdout, "3. compute_baseline finish\n");

    int8kernel(sc, sa, sb, m, k, n, n, NULL, NULL);
    fprintf(stdout, "** compute_new finish\n");
    fprintf(stdout, "----- print myresult:\n");
    print_int32_matrix(sc, m, n, n);


    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int idx = i * n + j;
            if (c[idx] != sc[idx]) {
                fprintf(stdout, " int8kernel err in [%d, %d]\n", i, j);    
                exit(-1);
            }
        }
    }
    fprintf(stdout, "** check result passed\n");


    free(a);
    free(sa);
    free(sa_as);

    free(sb);
    free(b);

    free(c);
    free(sc);
    return 0;
}

int main() {
   // test m k n
   // for (int kk = 1; kk < 25; ++kk) {
   //     test(4, kk, 1, 1);
   // }

   //  for (int nn = 1; nn < 15; ++nn) {
   //      test(4, 1, nn, nn);
   //  }

for (int m = 1; m < 50; ++m )
for(int n = 1; n < 50; ++n) {
    for (int k = 1; k < 50; ++k) {
        test(m, k, n, n);        
    }
}
//    test(4, 4, 1, 1);
    
    return 0;
}
