/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef APP_USBD_STRING_CONFIG_H
#define APP_USBD_STRING_CONFIG_H

#include "platforms.h"

/**
 * @defgroup app_usbd_string_conf USBD string configuration
 * @ingroup app_usbd_string_desc
 *
 * @brief @tagAPI52840 Configuration of the string module that can be easily affected by the final
 * user.
 * @{
 */

/**
 * @brief Supported languages identifiers
 *
 * Comma separated list of supported languages.
 */
#define APP_USBD_STRINGS_LANGIDS \
    (0x0409) // English (US) @avtolstoy: no idea why APP_USBD_XXX don't work correctly ((uint16_t)APP_USBD_LANG_ENGLISH | (uint16_t)APP_USBD_SUBLANG_ENGLISH_US)

/**
 * @brief Manufacturer name string descriptor
 *
 * Comma separated list of manufacturer names for each defined language.
 * Use @ref APP_USBD_STRING_DESC macro to create string descriptor.
 *
 * The order of manufacturer names has to be the same like in
 * @ref APP_USBD_STRINGS_LANGIDS.
 */
#define APP_USBD_STRINGS_MANUFACTURER    \
    APP_USBD_STRING_DESC("Particle")

/**
 * @brief Define whether @ref APP_USBD_STRINGS_MANUFACTURER is created by @ref APP_USBD_STRING_DESC
 * or declared as global variable.
 * */
#define APP_USBD_STRINGS_MANUFACTURER_EXTERN 0

/**
 * @brief Product name string descriptor
 *
 * List of product names defined the same way like in @ref APP_USBD_STRINGS_MANUFACTURER
 */
#if PLATFORM_ID == PLATFORM_BORON
#define APP_USBD_STRINGS_PRODUCT         \
    APP_USBD_STRING_DESC("Boron CDC Mode")
#elif PLATFORM_ID == PLATFORM_ESOMX
#define APP_USBD_STRINGS_PRODUCT         \
    APP_USBD_STRING_DESC("E SoM X CDC Mode")
#elif PLATFORM_ID == PLATFORM_BSOM
#define APP_USBD_STRINGS_PRODUCT         \
    APP_USBD_STRING_DESC("B SoM CDC Mode")
#else 
    #error "Unknown boron variant"
#endif // PLATFORM_ID == PLATFORM_BORON

/**
 * @brief Define whether @ref APP_USBD_STRINGS_PRODUCT is created by @ref APP_USBD_STRING_DESC
 * or declared as global variable.
 * */
#define APP_USBD_STRINGS_PRODUCT_EXTERN 0

/**
 * @brief Serial number string descriptor
 *
 * Create serial number string descriptor using @ref APP_USBD_STRING_DESC,
 * or configure it to point to any internal variable pointer filled with descriptor.
 *
 * @note
 * There is only one SERIAL number inside the library and it is Language independent.
 */
#define APP_USBD_STRING_SERIAL          g_extern_serial_number

/**
 * @brief Define whether @ref APP_USBD_STRING_SERIAL is created by @ref APP_USBD_STRING_DESC
 * or declared as global variable.
 * */
#define APP_USBD_STRING_SERIAL_EXTERN 1

/**
 * @brief User strings default values
 *
 * This value stores all application specific user strings with its default initialization.
 * The setup is done by X-macros.
 * Expected macro parameters:
 * @code
 * X(mnemonic, [=str_idx], ...)
 * @endcode
 * - @c mnemonic: Mnemonic of the string descriptor that would be added to
 *                @ref app_usbd_string_desc_idx_t enumerator.
 * - @c str_idx : String index value, may be set or left empty.
 *                For example WinUSB driver requires descriptor to be present on 0xEE index.
 *                Then use X(USBD_STRING_WINUSB, =0xEE, (APP_USBD_STRING_DESC(...)))
 * - @c ...     : List of string descriptors for each defined language.
 */
#if PLATFORM_ID == PLATFORM_BORON
#define APP_USBD_STRINGS_USER \
    X(APP_USER_1, , APP_USBD_STRING_DESC("Boron Serial")) \
    X(USBD_CONTROL_STRING_IDX, , APP_USBD_STRING_DESC("Boron Control Interface")) \
    X(USBD_WCID_STRING_IDX, = 0xee, APP_USBD_STRING_DESC("MSFT100\xee"))
#elif PLATFORM_ID == PLATFORM_BSOM
#define APP_USBD_STRINGS_USER \
    X(APP_USER_1, , APP_USBD_STRING_DESC("B SoM Serial")) \
    X(USBD_CONTROL_STRING_IDX, , APP_USBD_STRING_DESC("B SoM Control Interface")) \
    X(USBD_WCID_STRING_IDX, = 0xee, APP_USBD_STRING_DESC("MSFT100\xee"))
#elif PLATFORM_ID == PLATFORM_ESOMX
#define APP_USBD_STRINGS_USER \
    X(APP_USER_1, , APP_USBD_STRING_DESC("E SoM X Serial")) \
    X(USBD_CONTROL_STRING_IDX, , APP_USBD_STRING_DESC("E SoM X Control Interface")) \
    X(USBD_WCID_STRING_IDX, = 0xee, APP_USBD_STRING_DESC("MSFT100\xee"))
#else 
    #error "Unknown boron variant"
#endif // PLATFORM_ID == PLATFORM_BORON

/** @} */
#endif /* APP_USBD_STRING_CONFIG_H */
