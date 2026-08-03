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
#include "eagletrt-api.h"
#include "das/can-communication-api.h"
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

        /* FDCAN1 interrupt Init */
        HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
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

        /* FDCAN2 interrupt Init */
        HAL_NVIC_SetPriority(FDCAN2_IT0_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);
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

        /* FDCAN3 interrupt Init */
        HAL_NVIC_SetPriority(FDCAN3_IT0_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(FDCAN3_IT0_IRQn);
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

        /* FDCAN1 interrupt Deinit */
        HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
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

        /* FDCAN2 interrupt Deinit */
        HAL_NVIC_DisableIRQ(FDCAN2_IT0_IRQn);
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

        /* FDCAN3 interrupt Deinit */
        HAL_NVIC_DisableIRQ(FDCAN3_IT0_IRQn);
        /* USER CODE BEGIN FDCAN3_MspDeInit 1 */

        /* USER CODE END FDCAN3_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */
EAGLETRT_STATIC_INLINE enum CanCommunicationNetwork prv_can_get_network(
    const FDCAN_HandleTypeDef *hfdcan) {
    if (hfdcan == NULL) {
        return CAN_COMMUNICATION_NETWORK_COUNT;
    }

    switch ((uintptr_t)hfdcan->Instance) {
        case FDCAN1_BASE:
            return CAN_COMMUNICATION_NETWORK_PRIMARY;

        case FDCAN2_BASE:
            return CAN_COMMUNICATION_NETWORK_SECONDARY;

        case FDCAN3_BASE:
            return CAN_COMMUNICATION_NETWORK_DAS;

        default:
            return CAN_COMMUNICATION_NETWORK_COUNT;
    }
}

EAGLETRT_STATIC_INLINE FDCAN_HandleTypeDef *prv_can_get_handler(
    enum CanCommunicationNetwork network) {
    switch (network) {
        case CAN_COMMUNICATION_NETWORK_PRIMARY:
            return &hfdcan1;

        case CAN_COMMUNICATION_NETWORK_SECONDARY:
            return &hfdcan2;

        case CAN_COMMUNICATION_NETWORK_DAS:
            return &hfdcan3;

        default:
            return NULL;
    }
}

EAGLETRT_STATIC_INLINE uint32_t prv_can_length_to_fdcan_dlc(uint8_t length) {
    switch (length) {
        case 0U:
            return FDCAN_DLC_BYTES_0;

        case 1U:
            return FDCAN_DLC_BYTES_1;

        case 2U:
            return FDCAN_DLC_BYTES_2;

        case 3U:
            return FDCAN_DLC_BYTES_3;

        case 4U:
            return FDCAN_DLC_BYTES_4;

        case 5U:
            return FDCAN_DLC_BYTES_5;

        case 6U:
            return FDCAN_DLC_BYTES_6;

        case 7U:
            return FDCAN_DLC_BYTES_7;

        case 8U:
            return FDCAN_DLC_BYTES_8;

        default:
            return 0xFFFFFFFFU;
    }
}

EAGLETRT_STATIC_INLINE uint8_t prv_fdcan_dlc_to_can_length(uint32_t dlc) {
    switch (dlc) {
        case FDCAN_DLC_BYTES_0:
            return 0U;

        case FDCAN_DLC_BYTES_1:
            return 1U;

        case FDCAN_DLC_BYTES_2:
            return 2U;

        case FDCAN_DLC_BYTES_3:
            return 3U;

        case FDCAN_DLC_BYTES_4:
            return 4U;

        case FDCAN_DLC_BYTES_5:
            return 5U;

        case FDCAN_DLC_BYTES_6:
            return 6U;

        case FDCAN_DLC_BYTES_7:
            return 7U;

        case FDCAN_DLC_BYTES_8:
            return 8U;

        default:
            return 0xFFU;
    }
}

EAGLETRT_STATIC enum CanCommunicationReturnCode prv_can_send_to_hardware(
    enum CanCommunicationNetwork network,
    const struct CanCommunicationFrame *frame) {
    if (frame == NULL) {
        return CAN_COMMUNICATION_RC_NULL_POINTER;
    }

    if (frame->length > CAN_COMMUNICATION_FRAME_DATA_SIZE) {
        return CAN_COMMUNICATION_RC_INVALID_LENGTH;
    }

    FDCAN_HandleTypeDef *hfdcan = prv_can_get_handler(network);
    if (hfdcan == NULL) {
        return CAN_COMMUNICATION_RC_NULL_POINTER;
    }

    uint32_t dlc = prv_can_length_to_fdcan_dlc(frame->length);
    if (dlc == 0xFFFFFFFFU) {
        return CAN_COMMUNICATION_RC_INVALID_LENGTH;
    }

    FDCAN_TxHeaderTypeDef header = {
        .Identifier = frame->id,
        .IdType = FDCAN_STANDARD_ID,
        .TxFrameType = FDCAN_DATA_FRAME,
        .DataLength = dlc,
        .ErrorStateIndicator = FDCAN_ESI_ACTIVE,
        .BitRateSwitch = FDCAN_BRS_OFF,
        .FDFormat = FDCAN_CLASSIC_CAN,
        .TxEventFifoControl = FDCAN_NO_TX_EVENTS,
        .MessageMarker = 0U,
    };

    if (HAL_FDCAN_AddMessageToTxFifoQ(hfdcan,
                                      &header,
                                      (uint8_t *)frame->data) != HAL_OK) {
        return CAN_COMMUNICATION_RC_TRANSMISSION_ERROR;
    }

    return CAN_COMMUNICATION_RC_OK;
}

enum CanCommunicationReturnCode fdcan_send_primary(
    const struct CanCommunicationFrame *frame) {
    return prv_can_send_to_hardware(CAN_COMMUNICATION_NETWORK_PRIMARY, frame);
}

enum CanCommunicationReturnCode fdcan_send_secondary(
    const struct CanCommunicationFrame *frame) {
    return prv_can_send_to_hardware(CAN_COMMUNICATION_NETWORK_SECONDARY, frame);
}

enum CanCommunicationReturnCode fdcan_send_private(
    const struct CanCommunicationFrame *frame) {
    return prv_can_send_to_hardware(CAN_COMMUNICATION_NETWORK_DAS, frame);
}

EAGLETRT_STATIC void prv_can_receive_from_hardware(
    FDCAN_HandleTypeDef *hfdcan,
    uint32_t rx_fifo) {
    FDCAN_RxHeaderTypeDef header = { 0 };
    struct CanCommunicationFrame frame = { 0 };

    if (HAL_FDCAN_GetRxMessage(hfdcan,
                               rx_fifo,
                               &header,
                               frame.data) != HAL_OK) {
        return;
    }

    frame.id = header.Identifier;
    frame.length = prv_fdcan_dlc_to_can_length(header.DataLength);

    if (frame.length > CAN_COMMUNICATION_FRAME_DATA_SIZE) {
        return;
    }

    enum CanCommunicationNetwork network = prv_can_get_network(hfdcan);
    if (network >= CAN_COMMUNICATION_NETWORK_COUNT) {
        return;
    }

    EAGLETRT_API_UNUSED(can_communication_api_add_to_rx(network, &frame));
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan,
                               uint32_t rx_fifo0_its) {
    if ((rx_fifo0_its & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) == 0U) {
        return;
    }

    prv_can_receive_from_hardware(hfdcan, FDCAN_RX_FIFO0);

    EAGLETRT_API_UNUSED(HAL_FDCAN_ActivateNotification(
        hfdcan,
        FDCAN_IT_RX_FIFO0_NEW_MESSAGE,
        0U));
}

void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan,
                               uint32_t rx_fifo1_its) {
    if ((rx_fifo1_its & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) == 0U) {
        return;
    }

    prv_can_receive_from_hardware(hfdcan, FDCAN_RX_FIFO1);

    EAGLETRT_API_UNUSED(HAL_FDCAN_ActivateNotification(
        hfdcan,
        FDCAN_IT_RX_FIFO1_NEW_MESSAGE,
        0U));
}
/* USER CODE END 1 */
