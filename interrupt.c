* The assembly language code below handles CPU exception processing. This
 * code should not be modified; instead, the C language code in the function
 * interrupt_handler() can be modified as needed for a given application.
*/
void the_exception(void) __attribute__((section(".exceptions")));
void the_exception(void)
/*******************************************************************************
 * Exceptions code. By giving the code a section attribute with the name
 * ".exceptions" we allow the linker program to locate this code at the proper
 * exceptions vector address.
 * This code calls the interrupt handler and later returns from the exception.
 ******************************************************************************/
{
asm("subi sp, sp, 128");
asm("stw et, 96(sp)");
asm("rdctl et, ctl4");
asm("beq et, r0, SKIP_EA_DEC"); // Interrupt is not external
asm("subi ea, ea, 4"); /* Must decrement ea by one instruction
                                        * for external interupts, so that the
                                        * interrupted instruction will be run */
asm("SKIP_EA_DEC:");
asm("stw r1, 4(sp)"); // Save all registers asm("stw r2, 8(sp)")
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw
asm("stw

//r25=bt // above) //r26=gp
(skip r24 = et, because it is saved
asm("call
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
r5,  20(sp)");
r6,  24(sp)");
r7,  28(sp)");
r8,  32(sp)");
r9,  36(sp)");
r10, 40(sp)");
r11, 44(sp)");
r12, 48(sp)");
r13, 52(sp)");
r14, 56(sp)");
r15, 60(sp)");
r16, 64(sp)");
r17, 68(sp)");
r18, 72(sp)");
DE1-SOC COMPUTER SYSTEM WITH NIOS® II
For Quartus® Prime 17.1
 // skip r27 because it is sp, and there is no point in saving this
r28, 112(sp)");
r29, 116(sp)");
r30, 120(sp)");
r31, 124(sp)");
interrupt_handler"); // Call the C language interrupt handler
r1, 4(sp)"); // Restore all registers r2, 8(sp)");
r3, 12(sp)");
r4, 16(sp)");
asm("stw
asm("stw
asm("stw
asm("stw
asm("addi   fp,  sp, 128");
//r28=fp //r29=ea //r30=ba //r31=ra
November 2017

asm("addi   sp,  sp, 128");
    asm("eret");
}
DE1-SOC COMPUTER SYSTEM WITH NIOS® II
For Quartus® Prime 17.1
 asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
asm("ldw
// skip r27 because it is sp, and we did not save this on the stack
asm("ldw
asm("ldw
asm("ldw
asm("ldw
r28, 112(sp)");
r29, 116(sp)");
r30, 120(sp)");
r31, 124(sp)");
//r28=fp //r29=ea //r30=ba //r31=ra
r19, 76(sp)");
r20, 80(sp)");
r21, 84(sp)");
r22, 88(sp)");
r23, 92(sp)");
r24, 96(sp)");
r25, 100(sp)"); // r25 = bt r26, 104(sp)"); // r26 = gp
/******************************************************************************
 * Interrupt Service Routine
subroutine.
void interrupt_handler(void) { int ipending;
NIOS2_READ_IPENDING(ipending);
if (ipending & 0x1) // interval timer is interrupt level 0 {
        interval_timer_ISR();
    }
if (ipending & 0x2) // pushbuttons are interrupt level 1 {
        pushbutton_ISR();
    }
    // else, ignore the interrupt
return; }