#ifndef __CRYPTO_H__
#define __CRYPTO_H__


/*
 * mis_mix_1 - Algorithm to generate t1 from token. 
 *             t1 is used in key exchange.
 *
 * @param[in]   in   - The input token
 * @param[in]   mmac - Master public address
 * @param[in]   smac - Slave public address
 * @param[in]   pid  - Product ID
 * @param[out]  out  - The generated output token
 */
void mis_mix_1(uint8_t* in, uint8_t* mmac, uint8_t* smac, uint8_t* pid, uint8_t* out);



/*
 * mis_mix_2 - Algorithm to generate t2 from t1. 
 *             t2 is used in key exchange.
 *
 * @param[in]   in   - The input token
 * @param[in]   mmac - Master public address
 * @param[in]   smac - Slave public address
 * @param[in]   pid  - Product ID
 * @param[out]  out  - The generated output token
 */
void mis_mix_2(uint8_t* in, uint8_t* mmac, uint8_t* smac, uint8_t* pid, uint8_t* out);

/*
 * mis_encrypt - Encryption API in mi service
 *
 * @param[in]   in     - The input token
 * @param[in]   inLen  - Master public address
 * @param[in]   key    - Slave public address
 * @param[in]   keyLen - Product ID
 * @param[out]  out    - The generated output token
 */
void mis_encrypt(uint8_t* in, int inLen, uint8_t* key, int keyLen, uint8_t* out);

/*
 * mis_decrypt - Decryption API in mi service
 *
 * @param[in]   in     - The input token
 * @param[in]   inLen  - Master public address
 * @param[in]   key    - Slave public address
 * @param[in]   keyLen - Product ID
 * @param[out]  out    - The generated output token
 */
#define mis_decrypt    mis_encrypt




#endif  /* __CRYPTO_H__ */



