#include "can-communication.h"

/*!
 * \brief Function for incoming CAN frames on primary network.
 * \param[in] frame The frame just removed from the RX queue.
 * \retval CAN_COMMUNICATION_RC_OK on success.
 * \retval CAN_COMMUNICATION_RC_RECEIVE_HANDLER_ERROR if dispatch fails.
 */
enum CanCommunicationReturnCode can_communication_router_api_receive_primary(const struct CanCommunicationFrame *frame);

/*!
 * \brief Function for incoming CAN frames on secondary network.
 * \param[in] frame The frame just removed from the RX queue.
 * \retval CAN_COMMUNICATION_RC_OK on success.
 * \retval CAN_COMMUNICATION_RC_RECEIVE_HANDLER_ERROR if dispatch fails.
 */
enum CanCommunicationReturnCode can_communication_router_api_receive_secondary(const struct CanCommunicationFrame *frame);

/*!
 * \brief Function for incoming CAN frames on private network.
 * \param[in] frame The frame just removed from the RX queue.
 * \retval CAN_COMMUNICATION_RC_OK on success.
 * \retval CAN_COMMUNICATION_RC_RECEIVE_HANDLER_ERROR if dispatch fails.
 */
enum CanCommunicationReturnCode can_communication_router_api_receive_private(const struct CanCommunicationFrame *frame);
