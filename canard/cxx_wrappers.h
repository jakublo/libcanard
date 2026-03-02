/*
 * Copyright (c) 2022 Siddharth B Purohit, CubePilot Pty Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "helpers.h"

/// @brief Broadcast message interface.
/// @param MSGTYPE message type name
/// @param MSG_ID message id
/// @param MSG_SIGNATURE message signature
/// @param MSG_MAX_SIZE maximum message size
#if CANARD_ENABLE_CANFD || CANARD_ENABLE_TAO_OPTION
#define BROADCAST_MESSAGE_CXX_IFACE(MSGTYPE, MSG_ID, MSG_SIGNATURE, MSG_MAX_SIZE) \
    class MSGTYPE##_cxx_iface { \
    public: \
        typedef MSGTYPE msgtype; \
        static uint32_t (*encode)(msgtype*, uint8_t*, bool); \
        static bool (*decode)(const CanardRxTransfer* transfer, msgtype*); \
        static const uint16_t ID = MSG_ID; \
        static const uint64_t SIGNATURE = MSG_SIGNATURE; \
        static const uint16_t MAX_SIZE = MSG_MAX_SIZE; \
    }; \
    uint32_t (*MSGTYPE##_cxx_iface::encode)(msgtype*, uint8_t*, bool) = MSGTYPE##_encode; \
    bool (*MSGTYPE##_cxx_iface::decode)(const CanardRxTransfer* transfer, msgtype*) = MSGTYPE##_decode;
#else
#define BROADCAST_MESSAGE_CXX_IFACE(MSGTYPE, MSG_ID, MSG_SIGNATURE, MSG_MAX_SIZE) \
    class MSGTYPE##_cxx_iface { \
    public: \
        typedef MSGTYPE msgtype; \
        static uint32_t (*encode)(msgtype*, uint8_t*); \
        static bool (*decode)(const CanardRxTransfer* transfer, msgtype*); \
        static const uint16_t ID = MSG_ID; \
        static const uint64_t SIGNATURE = MSG_SIGNATURE; \
        static const uint16_t MAX_SIZE = MSG_MAX_SIZE; \
    }; \
    uint32_t (*MSGTYPE##_cxx_iface::encode)(msgtype*, uint8_t*) = MSGTYPE##_encode; \
    bool (*MSGTYPE##_cxx_iface::decode)(const CanardRxTransfer* transfer, msgtype*) = MSGTYPE##_decode;
#endif

#if CANARD_ENABLE_CANFD || CANARD_ENABLE_TAO_OPTION
#define SERVICE_MESSAGE_CXX_IFACE(SVCTYPE, SVC_ID, SVC_SIGNATURE, SVC_REQUEST_MAX_SIZE, SVC_RESPONSE_MAX_SIZE) \
    class SVCTYPE##_cxx_iface { \
    public: \
        typedef SVCTYPE##Request reqtype; \
        typedef SVCTYPE##Response rsptype; \
        static uint32_t (*req_encode)(reqtype*, uint8_t*, bool); \
        static uint32_t (*rsp_encode)(rsptype*, uint8_t*, bool); \
        static bool (*req_decode)(const CanardRxTransfer* transfer, reqtype*); \
        static bool (*rsp_decode)(const CanardRxTransfer* transfer, rsptype*); \
        static const uint16_t ID = SVC_ID; \
        static const uint64_t SIGNATURE = SVC_SIGNATURE; \
        static const uint16_t REQ_MAX_SIZE = SVC_REQUEST_MAX_SIZE; \
        static const uint16_t RSP_MAX_SIZE = SVC_RESPONSE_MAX_SIZE; \
    }; \
    uint32_t (*SVCTYPE##_cxx_iface::req_encode)(reqtype*, uint8_t*, bool) = SVCTYPE##Request_encode; \
    uint32_t (*SVCTYPE##_cxx_iface::rsp_encode)(rsptype*, uint8_t*, bool) = SVCTYPE##Response_encode; \
    bool (*SVCTYPE##_cxx_iface::req_decode)(const CanardRxTransfer* transfer, reqtype*) = SVCTYPE##Request_decode; \
    bool (*SVCTYPE##_cxx_iface::rsp_decode)(const CanardRxTransfer* transfer, rsptype*) = SVCTYPE##Response_decode;
#else
/// @brief Service message interface.
/// @param SVCTYPE message type name
/// @param SVC_ID message id
/// @param SVC_SIGNATURE message signature
/// @param SVC_REQUEST_MAX_SIZE maximum request size
/// @param SVC_RESPONSE_MAX_SIZE maximum response size
#define SERVICE_MESSAGE_CXX_IFACE(SVCTYPE, SVC_ID, SVC_SIGNATURE, SVC_REQUEST_MAX_SIZE, SVC_RESPONSE_MAX_SIZE) \
    class SVCTYPE##_cxx_iface { \
    public: \
        typedef SVCTYPE##Request reqtype; \
        typedef SVCTYPE##Response rsptype; \
        static uint32_t (*req_encode)(reqtype*, uint8_t*); \
        static uint32_t (*rsp_encode)(rsptype*, uint8_t*); \
        static bool (*req_decode)(const CanardRxTransfer* transfer, reqtype*); \
        static bool (*rsp_decode)(const CanardRxTransfer* transfer, rsptype*); \
        static const uint16_t ID = SVC_ID; \
        static const uint64_t SIGNATURE = SVC_SIGNATURE; \
        static const uint16_t REQ_MAX_SIZE = SVC_REQUEST_MAX_SIZE; \
        static const uint16_t RSP_MAX_SIZE = SVC_RESPONSE_MAX_SIZE; \
    }; \
    uint32_t (*SVCTYPE##_cxx_iface::req_encode)(reqtype*, uint8_t*) = SVCTYPE##Request_encode; \
    uint32_t (*SVCTYPE##_cxx_iface::rsp_encode)(rsptype*, uint8_t*) = SVCTYPE##Response_encode; \
    bool (*SVCTYPE##_cxx_iface::req_decode)(const CanardRxTransfer* transfer, reqtype*) = SVCTYPE##Request_decode; \
    bool (*SVCTYPE##_cxx_iface::rsp_decode)(const CanardRxTransfer* transfer, rsptype*) = SVCTYPE##Response_decode;
#endif
