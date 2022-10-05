/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/Dawid/Desktop/PTC/Laby3/Licznik/ck_divider.vhd";
extern char *IEEE_P_2592010699;

unsigned char ieee_p_2592010699_sub_1690584930_503743352(char *, unsigned char );


static void work_a_0409441500_3212880686_p_0(char *t0)
{
    unsigned char t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    unsigned char t6;
    unsigned char t7;
    char *t8;
    int t9;
    int t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;

LAB0:    xsi_set_current_line(22, ng0);
    t2 = (t0 + 992U);
    t3 = xsi_signal_has_event(t2);
    if (t3 == 1)
        goto LAB5;

LAB6:    t1 = (unsigned char)0;

LAB7:    if (t1 != 0)
        goto LAB2;

LAB4:
LAB3:    xsi_set_current_line(38, ng0);
    t2 = (t0 + 1992U);
    t4 = *((char **)t2);
    t1 = *((unsigned char *)t4);
    t2 = (t0 + 3992);
    t5 = (t2 + 56U);
    t8 = *((char **)t5);
    t11 = (t8 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = t1;
    xsi_driver_first_trans_fast_port(t2);
    t2 = (t0 + 3592);
    *((int *)t2) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(23, ng0);
    t4 = (t0 + 1352U);
    t8 = *((char **)t4);
    t9 = *((int *)t8);
    t10 = (t9 + 1);
    t4 = (t0 + 3672);
    t11 = (t4 + 56U);
    t12 = *((char **)t11);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    *((int *)t14) = t10;
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(24, ng0);
    t2 = (t0 + 1352U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t2 = (t0 + 2288U);
    t5 = *((char **)t2);
    t10 = *((int *)t5);
    t1 = (t9 == t10);
    if (t1 != 0)
        goto LAB8;

LAB10:    t2 = (t0 + 1512U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t2 = (t0 + 2288U);
    t5 = *((char **)t2);
    t10 = *((int *)t5);
    t1 = (t9 == t10);
    if (t1 != 0)
        goto LAB11;

LAB12:    t2 = (t0 + 1672U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t2 = (t0 + 2288U);
    t5 = *((char **)t2);
    t10 = *((int *)t5);
    t1 = (t9 == t10);
    if (t1 != 0)
        goto LAB13;

LAB14:    t2 = (t0 + 1832U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t2 = (t0 + 2288U);
    t5 = *((char **)t2);
    t10 = *((int *)t5);
    t1 = (t9 == t10);
    if (t1 != 0)
        goto LAB15;

LAB16:
LAB9:    goto LAB3;

LAB5:    t4 = (t0 + 1032U);
    t5 = *((char **)t4);
    t6 = *((unsigned char *)t5);
    t7 = (t6 == (unsigned char)3);
    t1 = t7;
    goto LAB7;

LAB8:    xsi_set_current_line(25, ng0);
    t2 = (t0 + 3672);
    t8 = (t2 + 56U);
    t11 = *((char **)t8);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    *((int *)t13) = 0;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(26, ng0);
    t2 = (t0 + 1512U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t10 = (t9 + 1);
    t2 = (t0 + 3736);
    t5 = (t2 + 56U);
    t8 = *((char **)t5);
    t11 = (t8 + 56U);
    t12 = *((char **)t11);
    *((int *)t12) = t10;
    xsi_driver_first_trans_fast(t2);
    goto LAB9;

LAB11:    xsi_set_current_line(28, ng0);
    t2 = (t0 + 3736);
    t8 = (t2 + 56U);
    t11 = *((char **)t8);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    *((int *)t13) = 0;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(29, ng0);
    t2 = (t0 + 1672U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t10 = (t9 + 1);
    t2 = (t0 + 3800);
    t5 = (t2 + 56U);
    t8 = *((char **)t5);
    t11 = (t8 + 56U);
    t12 = *((char **)t11);
    *((int *)t12) = t10;
    xsi_driver_first_trans_fast(t2);
    goto LAB9;

LAB13:    xsi_set_current_line(31, ng0);
    t2 = (t0 + 3800);
    t8 = (t2 + 56U);
    t11 = *((char **)t8);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    *((int *)t13) = 0;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(32, ng0);
    t2 = (t0 + 1832U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t10 = (t9 + 1);
    t2 = (t0 + 3864);
    t5 = (t2 + 56U);
    t8 = *((char **)t5);
    t11 = (t8 + 56U);
    t12 = *((char **)t11);
    *((int *)t12) = t10;
    xsi_driver_first_trans_fast(t2);
    goto LAB9;

LAB15:    xsi_set_current_line(34, ng0);
    t2 = (t0 + 3864);
    t8 = (t2 + 56U);
    t11 = *((char **)t8);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    *((int *)t13) = 0;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(35, ng0);
    t2 = (t0 + 1992U);
    t4 = *((char **)t2);
    t1 = *((unsigned char *)t4);
    t3 = ieee_p_2592010699_sub_1690584930_503743352(IEEE_P_2592010699, t1);
    t2 = (t0 + 3928);
    t5 = (t2 + 56U);
    t8 = *((char **)t5);
    t11 = (t8 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = t3;
    xsi_driver_first_trans_fast(t2);
    goto LAB9;

}


extern void work_a_0409441500_3212880686_init()
{
	static char *pe[] = {(void *)work_a_0409441500_3212880686_p_0};
	xsi_register_didat("work_a_0409441500_3212880686", "isim/twobit_counter_isim_beh.exe.sim/work/a_0409441500_3212880686.didat");
	xsi_register_executes(pe);
}
