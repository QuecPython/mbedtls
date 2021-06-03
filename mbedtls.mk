# Copyright (c) Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
#  
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#  
#     http://www.apache.org/licenses/LICENSE-2.0
#  
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

NAME := MBEDTLS

$(NAME)_SRCS = \
	library/aes.c \
	library/aesni.c \
	library/arc4.c \
	library/aria.c \
	library/asn1parse.c \
	library/asn1write.c \
	library/base64.c \
	library/bignum.c \
	library/blowfish.c \
	library/camellia.c \
	library/ccm.c \
	library/certs.c \
	library/chacha20.c \
	library/chachapoly.c \
	library/cipher.c \
	library/cipher_wrap.c \
	library/cmac.c \
	library/ctr_drbg.c \
	library/debug.c \
	library/des.c \
	library/dhm.c \
	library/ecdh.c \
	library/ecdsa.c \
	library/ecjpake.c \
	library/ecp.c \
	library/ecp_curves.c \
	library/entropy.c \
	library/entropy_poll.c \
	library/error.c \
	library/gcm.c \
	library/havege.c \
	library/hkdf.c \
	library/hmac_drbg.c \
	library/md.c \
	library/md2.c \
	library/md4.c \
	library/md5.c \
	library/memory_buffer_alloc.c \
	library/net_sockets.c \
	library/nist_kw.c \
	library/oid.c \
	library/padlock.c \
	library/pem.c \
	library/pk.c \
	library/pk_wrap.c \
	library/pkcs11.c \
	library/pkcs12.c \
	library/pkcs5.c \
	library/pkparse.c \
	library/pkwrite.c \
	library/platform.c \
	library/platform_util.c \
	library/poly1305.c \
	library/psa_crypto.c \
	library/psa_crypto_se.c \
	library/psa_crypto_slot_management.c \
	library/psa_crypto_storage.c \
	library/psa_its_file.c \
	library/ripemd160.c \
	library/rsa.c \
	library/rsa_internal.c \
	library/sha1.c \
	library/sha256.c \
	library/sha512.c \
	library/ssl_cache.c \
	library/ssl_ciphersuites.c \
	library/ssl_cli.c \
	library/ssl_cookie.c \
	library/ssl_msg.c \
	library/ssl_srv.c \
	library/ssl_ticket.c \
	library/ssl_tls.c \
	library/threading.c \
	library/timing.c \
	library/version.c \
	library/version_features.c \
	library/x509.c \
	library/x509_create.c \
	library/x509_crl.c \
	library/x509_crt.c \
	library/x509_csr.c \
	library/x509write_crt.c \
	library/x509write_csr.c \
	library/xtea.c \
	port/helios/src/mbedtls_init.c \
	port/helios/src/threading_alt.c \
	port/helios/src/timing_alt.c

$(NAME)_COMPONENTS = \
	system/platform/$(strip $(PLAT)) \
	system/lwip \
	system/fs \
	system/network

$(NAME)_CFLAGS = \
	-Wno-error=unused-parameter \
	-Wno-error=unused-function

ifeq ($(strip $(PLAT)),Unisoc)
$(NAME)_CFLAGS += --include=system/lwip/$(strip $(PLAT))/src/include/lwip/errno.h
endif

GLOBAL_INCS = \
	. \
	include \
	include/mbedtls \
	include/psa \
	library \
	port/helios/inc


