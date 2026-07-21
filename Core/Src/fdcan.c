/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.c
  * @brief   This file provides code for the configuration
  *          of the FDCAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "fdcan.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan1;
FDCAN_HandleTypeDef hfdcan2;
FDCAN_HandleTypeDef hfdcan3;

/* FDCAN1 init function */
void MX_FDCAN1_Init(void) {

    /* USER CODE BEGIN FDCAN1_Init 0 */

    /* USER CODE END FDCAN1_Init 0 */

    /* USER CODE BEGIN FDCAN1_Init 1 */

    /* USER CODE END FDCAN1_Init 1 */
    hfdcan1.Instance = FDCAN1;
    hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
    hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
    hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
    hfdcan1.Init.AutoRetransmission = DISABLE;
    hfdcan1.Init.TransmitPause = DISABLE;
    hfdcan1.Init.ProtocolException = DISABLE;
    hfdcan1.Init.NominalPrescaler = 16;
    hfdcan1.Init.NominalSyncJumpWidth = 1;
    hfdcan1.Init.NominalTimeSeg1 = 1;
    hfdcan1.Init.NominalTimeSeg2 = 1;
    hfdcan1.Init.DataPrescaler = 1;
    hfdcan1.Init.DataSyncJumpWidth = 1;
    hfdcan1.Init.DataTimeSeg1 = 1;
    hfdcan1.Init.DataTimeSeg2 = 1;
    hfdcan1.Init.StdFiltersNbr = 0;
    hfdcan1.Init.ExtFiltersNbr = 0;
    hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
    if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN FDCAN1_Init 2 */

    /* USER CODE END FDCAN1_Init 2 */
}
/* FDCAN2 init function */
void MX_FDCAN2_Init(void) {

    /* USER CODE BEGIN FDCAN2_Init 0 */

    /* USER CODE END FDCAN2_Init 0 */

    /* USER CODE BEGIN FDCAN2_Init 1 */

    /* USER CODE END FDCAN2_Init 1 */
    hfdcan2.Instance = FDCAN2;
    hfdcan2.Init.ClockDivider = FDCAN_CLOCK_DIV1;
    hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
    hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
    hfdcan2.Init.AutoRetransmission = DISABLE;
    hfdcan2.Init.TransmitPause = DISABLE;
    hfdcan2.Init.ProtocolException = DISABLE;
    hfdcan2.Init.NominalPrescaler = 16;
    hfdcan2.Init.NominalSyncJumpWidth = 1;
    hfdcan2.Init.NominalTimeSeg1 = 1;
    hfdcan2.Init.NominalTimeSeg2 = 1;
    hfdcan2.Init.DataPrescaler = 1;
    hfdcan2.Init.DataSyncJumpWidth = 1;
    hfdcan2.Init.DataTimeSeg1 = 1;
    hfdcan2.Init.DataTimeSeg2 = 1;
    hfdcan2.Init.StdFiltersNbr = 0;
    hfdcan2.Init.ExtFiltersNbr = 0;
    hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
    if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN FDCAN2_Init 2 */

    /* USER CODE END FDCAN2_Init 2 */
}
/* FDCAN3 init function */
void MX_FDCAN3_Init(void) {

    /* USER CODE BEGIN FDCAN3_Init 0 */

    /* USER CODE END FDCAN3_Init 0 */

    /* USER CODE BEGIN FDCAN3_Init 1 */

    /* USER CODE END FDCAN3_Init 1 */
    hfdcan3.Instance = FDCAN3;
    hfdcan3.Init.ClockDivider = FDCAN_CLOCK_DIV1;
    hfdcan3.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
    hfdcan3.Init.Mode = FDCAN_MODE_NORMAL;
    hfdcan3.Init.AutoRetransmission = DISABLE;
    hfdcan3.Init.TransmitPause = DISABLE;
    hfdcan3.Init.ProtocolException = DISABLE;
    hfdcan3.Init.NominalPrescaler = 16;
    hfdcan3.Init.NominalSyncJumpWidth = 1;
    hfdcan3.Init.NominalTimeSeg1 = 1;
    hfdcan3.Init.NominalTimeSeg2 = 1;
    hfdcan3.Init.DataPrescaler = 1;
    hfdcan3.Init.DataSyncJumpWidth = 1;
    hfdcan3.Init.DataTimeSeg1 = 1;
    hfdcan3.Init.DataTimeSeg2 = 1;
    hfdcan3.Init.StdFiltersNbr = 0;
    hfdcan3.Init.ExtFiltersNbr = 0;
    hfdcan3.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
    if (HAL_FDCAN_Init(&hfdcan3) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN FDCAN3_Init 2 */

    /* USER CODE END FDCAN3_Init 2 */
}

static uint32_t HAL_RCC_FDCAN_CLK_ENABLED = 0;

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef *fdcanHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };
    if (fdcanHandle->Instance == FDCAN1) {
        /* USER CODE BEGIN FDCAN1_MspInit 0 */

        /* USER CODE END FDCAN1_MspInit 0 */

        /** Initializes the peripherals clocks
  */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
            Error_Handler();
        }

        /* FDCAN1 clock enable */
        HAL_RCC_FDCAN_CLK_ENABLED++;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 1) {
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**FDCAN1 GPIO Configuration
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX
    */
        GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* USER CODE BEGIN FDCAN1_MspInit 1 */

        /* USER CODE END FDCAN1_MspInit 1 */
    } else if (fdcanHandle->Instance == FDCAN2) {
        /* USER CODE BEGIN FDCAN2_MspInit 0 */

        /* USER CODE END FDCAN2_MspInit 0 */

        /** Initializes the peripherals clocks
  */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
            Error_Handler();
        }

        /* FDCAN2 clock enable */
        HAL_RCC_FDCAN_CLK_ENABLED++;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 1) {
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**FDCAN2 GPIO Configuration
    PB12     ------> FDCAN2_RX
    PB6     ------> FDCAN2_TX
    */
        GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* USER CODE BEGIN FDCAN2_MspInit 1 */

        /* USER CODE END FDCAN2_MspInit 1 */
    } else if (fdcanHandle->Instance == FDCAN3) {
        /* USER CODE BEGIN FDCAN3_MspInit 0 */

        /* USER CODE END FDCAN3_MspInit 0 */

        /** Initializes the peripherals clocks
  */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
        PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
            Error_Handler();
        }

        /* FDCAN3 clock enable */
        HAL_RCC_FDCAN_CLK_ENABLED++;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 1) {
            __HAL_RCC_FDCAN_CLK_ENABLE();
        }

        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**FDCAN3 GPIO Configuration
    PA15     ------> FDCAN3_TX
    PB3     ------> FDCAN3_RX
    */
        GPIO_InitStruct.Pin = GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF11_FDCAN3;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF11_FDCAN3;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* USER CODE BEGIN FDCAN3_MspInit 1 */

        /* USER CODE END FDCAN3_MspInit 1 */
    }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef *fdcanHandle) {

    if (fdcanHandle->Instance == FDCAN1) {
        /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

        /* USER CODE END FDCAN1_MspDeInit 0 */
        /* Peripheral clock disable */
        HAL_RCC_FDCAN_CLK_ENABLED--;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 0) {
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        /**FDCAN1 GPIO Configuration
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX
    */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11 | GPIO_PIN_12);

        /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

        /* USER CODE END FDCAN1_MspDeInit 1 */
    } else if (fdcanHandle->Instance == FDCAN2) {
        /* USER CODE BEGIN FDCAN2_MspDeInit 0 */

        /* USER CODE END FDCAN2_MspDeInit 0 */
        /* Peripheral clock disable */
        HAL_RCC_FDCAN_CLK_ENABLED--;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 0) {
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        /**FDCAN2 GPIO Configuration
    PB12     ------> FDCAN2_RX
    PB6     ------> FDCAN2_TX
    */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12 | GPIO_PIN_6);

        /* USER CODE BEGIN FDCAN2_MspDeInit 1 */

        /* USER CODE END FDCAN2_MspDeInit 1 */
    } else if (fdcanHandle->Instance == FDCAN3) {
        /* USER CODE BEGIN FDCAN3_MspDeInit 0 */

        /* USER CODE END FDCAN3_MspDeInit 0 */
        /* Peripheral clock disable */
        HAL_RCC_FDCAN_CLK_ENABLED--;
        if (HAL_RCC_FDCAN_CLK_ENABLED == 0) {
            __HAL_RCC_FDCAN_CLK_DISABLE();
        }

        /**FDCAN3 GPIO Configuration
    PA15     ------> FDCAN3_TX
    PB3     ------> FDCAN3_RX
    */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_15);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3);

        /* USER CODE BEGIN FDCAN3_MspDeInit 1 */

        /* USER CODE END FDCAN3_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */
/*!
 * \brief Returns the CAN network used based on the native ST HAL CAN handle.
 * \warning If the \c hfdcan refers to an undefined instance, the returned value is a non-valid network (\c CAN_COMM_NET_COUNT).
 * \param[in] hfdcan Pointer to the ST HAL CAN handle instance structure.
 * \retval CAN_COMM_NET_PRIMARY If the handler refers to the primary network peripheral instance.
 * \retval CAN_COMM_NET_SECONDARY If the handler refers to the secondary network peripheral instance.
 * \retval CAN_COMM_NET_PRIVATE If the handler refers to the inverter network peripheral instance.
 * \retval CAN_COMM_NET_COUNT If the handler doesn't refer to any valid CAN network.
 */
EAGLETRT_STATIC_INLINE enum CanCommunicationNetwork prv_can_get_network(const CAN_HandleTypeDef *hfdcan) {
    if (hfdcan == NULL || hfdcan->Instance == NULL) {
        return CAN_COMM_NET_COUNT;
    }

    if (hfdcan->Instance == FDCAN1) {
        return CAN_COMM_NET_PRIMARY;
    }

    if (hfdcan->Instance == FDCAN2) {
        return CAN_COMM_NET_SECONDARY;
    }

    if (hfdcan->Instance == FDCAN3) {
        return CAN_COMM_NET_PRIVATE;
    }

    return CAN_COMM_NET_COUNT;
}

/*!
 * \brief Returns the native ST HAL CAN handler based on the network enum.
 * \param[in] network The target network track enum.
 * \return Pointer to the matched global CAN_HandleTypeDef, or \c NULL if invalid.
 */
EAGLETRT_STATIC_INLINE CAN_HandleTypeDef *prv_can_get_handler(enum CanCommunicationNetwork network) {
    switch (network) {
        case CAN_COMM_NET_PRIMARY:
            return &hfdcan1;
        case CAN_COMM_NET_SECONDARY:
            return &hfdcan2;
        case CAN_COMM_NET_PRIVATE:
            return &hfdcan3;
        default:
            return NULL;
    }
}

/*!
 * \brief Internal unified helper to write an abstract frame out to an ST HAL CAN peripheral.
 * \param[in] network The network track enum indicating which hardware peripheral to target.
 * \param[in] frame Pointer to the abstract frame structure containing the payload.
 *
 * \retval CAN_COMMUNICATION_RC_OK if the frame was sent successfully.
 * \retval CAN_COMMUNICATION_RC_NULL_POINTER if a required pointer configuration is \c NULL.
 * \retval CAN_COMMUNICATION_RC_INVALID_LENGTH if the frame length exceeds CAN_COMMUNICATION_FRAME_DATA_SIZE.
 * \retval CAN_COMMUNICATION_RC_TRANSMISSION_ERROR if the native HAL layer rejects the transmission.
 */
EAGLETRT_STATIC enum CanCommunicationReturnCode prv_can_send_to_hardware(enum CanCommunicationNetwork network, const struct CanCommunicationFrame *frame) {
    CAN_HandleTypeDef *hfdcan = prv_can_get_handler(network);

    if (hfdcan == NULL || frame == NULL) {
        return CAN_COMMUNICATION_RC_NULL_POINTER;
    }
    if (frame->length > CAN_COMMUNICATION_FRAME_DATA_SIZE) {
        return CAN_COMMUNICATION_RC_INVALID_LENGTH;
    }

    CAN_TxHeaderTypeDef tx_header;
    uint32_t tx_mailbox = 0U;

    tx_header.StdId = frame->id;
    tx_header.ExtId = 0U;
    tx_header.IDE = CAN_ID_STD;
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = frame->length;
    tx_header.TransmitGlobalTime = DISABLE;

    if (HAL_CAN_AddTxMessage(hfdcan, &tx_header, (uint8_t *)frame->data, &tx_mailbox) != HAL_OK) {
        return CAN_COMMUNICATION_RC_TRANSMISSION_ERROR;
    }

    return CAN_COMMUNICATION_RC_OK;
}

enum CanCommunicationReturnCode can_send_primary(const struct CanCommunicationFrame *frame) {
    return prv_can_send_to_hardware(CAN_COMM_NET_PRIMARY, frame);
}

enum CanCommunicationReturnCode can_send_secondary(const struct CanCommunicationFrame *frame) {
    return prv_can_send_to_hardware(CAN_COMM_NET_SECONDARY, frame);
}

enum CanCommunicationReturnCode can_send_private(const struct CanCommunicationFrame *frame) {
    return prv_can_send_to_hardware(CAN_COMM_NET_PRIVATE, frame);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hfdcan) {
    CAN_RxHeaderTypeDef header = { 0 };
    struct CanCommunicationFrame msg;

    if (HAL_CAN_GetRxMessage(hfdcan, CAN_RX_FIFO0, &header, msg.data) == HAL_OK) {
        msg.id = (header.IDE == CAN_ID_EXT) ? header.ExtId : header.StdId;
        msg.length = (uint8_t)header.DLC;

        // Based on the handler, retrieve the selected network
        enum CanCommunicationNetwork network = prv_can_get_network(hfdcan);

        if (network < CAN_COMM_NET_COUNT) {
            /*
            The return value of the call is not used as no action can be taken within the interrupt
            such as retry, waiting or heavy error-handling.
            It is possible, if needed, to add a logger line to let know the user that something
            bad happened during the queueing of the frame.
            */
            EAGLETRT_API_UNUSED(can_communication_api_add_to_rx(network, &msg));
        }
    }
}
/* USER CODE END 1 */
