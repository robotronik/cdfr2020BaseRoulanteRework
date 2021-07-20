/**
 * @file
 *
 * This file is part of cdfr2020BaseRoulante
 *
 * @brief This implements the setup of CAN protocol to allow F3, F4 and other
 *        potential computers to communicate
 *        Source: https://www.rhye.org/post/stm32-with-opencm3-3-canbus/
 *
 * @date  10/2020
 *
 * Licence :
 *
 * Robotronik Phelma
 * @author NPXav Benano JamesWright KameradJS(Nornort)
 */

#include "canmsgs.h"
#include <stdlib.h>

void can_setup() {
  int status = 96;
  // Enable clock to the CAN peripheral
  rcc_periph_clock_enable(RCC_CAN1);

  //set alternate function on the pin to use CAN
  //FIXME: pullup sur RX ?
  // PP sur TX ?
  _gpio_setup_pin_af(CAN1_RX_RCC,CAN1_RX_PORT,CAN1_RX_PIN,CAN1_RX_AF,GPIO_PUPD_NONE,GPIO_OTYPE_OD);
  _gpio_setup_pin_af(CAN1_TX_RCC,CAN1_TX_PORT,CAN1_TX_PIN,CAN1_TX_AF,GPIO_PUPD_NONE,GPIO_OTYPE_PP);

  // CAN RX
  // rcc_periph_clock_enable(CAN1_RX_RCC);
  // gpio_mode_setup(CAN1_RX_PORT, GPIO_MODE_AF,
  //                 GPIO_PUPD_PULLUP, CAN1_RX_PIN);
  // gpio_set_af(CAN1_RX_PORT, CAN1_RX_AF, CAN1_RX_PIN);
  // // gpio_set_output_options(CAN1_RX_PORT, GPIO_OTYPE_OD,
  // //                       GPIO_SOSPEED_50MHZ, CAN1_RX_PIN);
  
  // // // CAN TX
  // rcc_periph_clock_enable(CAN1_TX_RCC);
  // gpio_set_af(CAN1_TX_PORT, CAN1_TX_AF, CAN1_TX_PIN);
  // // gpio_set_output_options(CAN1_TX_PORT, GPIO_OTYPE_PP,
  // //                         GPIO_OSPEED_50MHZ, CAN1_TX_PIN);
  // gpio_mode_setup(CAN1_TX_PORT, GPIO_MODE_AF,
  //                 GPIO_PUPD_NONE, CAN1_TX_PIN);

  // Reset the CAN peripheral
  can_reset(CAN1);

  // Initialize the CAN peripheral
  // return 0 if success, 1 if failure
  status = can_init(CAN1,  // The CAN ID
           false, // Time Trigger Communication mode? No
           true,  // Automatic bus-off management? 
           true,  // Automatic wakeup mode? Wakeup on message rx
           true, // No automatic transmit? Do auto-retry IF False auto-retry, if TRUE only one TRY
           false, // Receive FIFO locked mode? Discard older messages over newer
           false, // Transmit FIFO priority ? Tx priority based on identifier
           // Bit timing settings
           PARAM_SJW, // Resync time quanta jump width
           PARAM_TS1, // Time segment 1 time quanta width
           PARAM_TS2, // Time segment 2 time quanta width
           PARAM_BRP, // Baudrate prescaler
           // Loopback mode
           true, // If set, can RX and can TX are internally linked, for testing purposes
           // Silent mode
           false); // If set, CAN can receive but not transmit
  fprintf(stderr,"setup status: %d\n",status);
  // uint32_t reg = PARAM_SJW+PARAM_TS1+PARAM_TS2+PARAM_BRP;
  fprintf(stderr,"valeur du reg CAN_BTR: %lx\n",CAN_BTR(CAN1)); 

  // Enable CAN interrupts for FIFO message pending (FMPIE)
  // actually there are two FIFO so two interrupt for new messages to check
  can_enable_irq(CAN1, CAN_IER_FMPIE0 | CAN_IER_FMPIE1 ); 

  // Transmit mailbox empty interrupt enable
  // can_enable_irq(CAN1, CAN_IER_TMEIE);

  // Error interrupt enable
  can_enable_irq(CAN1, CAN_IER_ERRIE);

  fprintf(stderr,"valeur du reg CAN_IER: %lx\n",CAN_IER(CAN1)); 

  //enable the entries related to both FIFO in NVIC table
  nvic_enable_irq(NVIC_USB_LP_CAN1_RX0_IRQ);
  nvic_enable_irq(NVIC_CAN1_RX1_IRQ);
  nvic_enable_irq(NVIC_CAN1_SCE_IRQ);

  // 0..27 filter banks                                               
  // Initialisation filter bank 0
  // can_filter_id_mask_16bit_init(
  //   0,  // Filter bank 0
  //   0,  // id1
  //  	0,  // mask1
  //   0,  // id2
  //   0,  // mask2
  //  	0,  // FIFO 0
  //  	true); // enables the filter
  
    // Initialisation of filter bank 1
    // can_filter_id_mask_16bit_init(
    //   0,  // Filter bank 0
    //   0,  // id1
    //   0,  // mask1
    //   0,  // id2
    //   0,  // mask2
    //   1,  // FIFO 1
    //   true); // enables the filter
}

void can1_rx1_isr(){
  fprintf(stderr,"Message detected on fifo 1\n");

  uint32_t id = 0;
  uint8_t fmi,length;
  uint8_t pdata[2];
  uint16_t timestamp;
  bool ext,rtr;
  can_receive(CAN1,1,true,&id,&ext,&rtr,&fmi,&length,pdata,&timestamp);

  fprintf(stderr,"Message received is: id=%lx dlc=%d data=%x%x\n",id,length,pdata[0],pdata[1]);
}

void usb_lp_can1_rx0_isr(){
  fprintf(stderr,"Message detected on fifo 0\n");

  uint32_t id = 0;
  uint8_t fmi,length;
  uint8_t pdata[2];
  uint16_t timestamp;
  bool ext,rtr;
  can_receive(CAN1,0,true,&id,&ext,&rtr,&fmi,&length,pdata,&timestamp);

  fprintf(stderr,"Message received is: id=%lx dlc=%d data=%x%x\n",id,length,pdata[0],pdata[1]);
}

void can1_sce_isr(){
  fprintf(stderr, "sce interrupt");
}