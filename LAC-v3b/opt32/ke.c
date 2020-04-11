#include "api.h"
#include "rand.h"
#include <string.h>

//Alice send: generate pk and sk, and send pk to Bob
int crypto_ke_alice_send(uint8_t *pk,uint8_t *sk)
{
	//call key generation algorithm to get pk and sk
	kg(pk, sk);
	
	return 0;
}
// Bob receive: receive  pk, randomly choose m, and encryrpt m with pk to generate c, k=HASH(pk,m).
int crypto_ke_bob_receive(uint8_t *pk, uint8_t *c, uint8_t *k)
{
	uint8_t temp_key[MESSAGE_LEN];
	uint8_t in[MESSAGE_LEN+PK_LEN];
	unsigned long long clen;

	//call cpa secure kem to generate k2 
	random_bytes(temp_key,MESSAGE_LEN);
	pke_enc(pk,temp_key,MESSAGE_LEN,c,&clen);
	
	//call hash to compute  k=hash(pk,m)
	memcpy(in,pk,PK_LEN);
	memcpy(in+PK_LEN,temp_key,MESSAGE_LEN);
	hash_to_k(in,MESSAGE_LEN+PK_LEN,k);
	
	return 0;
}
//Alice receive: receive c, and decrypt to get m and comute k=HASH(pk,m)
int crypto_ke_alice_receive(uint8_t *pk, uint8_t *sk, uint8_t *c, uint8_t *k)
{
	uint8_t temp_key[MESSAGE_LEN];
	uint8_t in[MESSAGE_LEN+PK_LEN];
	unsigned long long mlen;

	//decrypt c of cca kem to get k2
	pke_dec(sk,c,CIPHER_LEN,temp_key,&mlen);
	
	//call hash to compute  k=hash(pk,m)
	memcpy(in,pk,PK_LEN);
	memcpy(in+PK_LEN,temp_key,MESSAGE_LEN);
	hash_to_k(in,MESSAGE_LEN+PK_LEN,k);
	
	return 0;
}