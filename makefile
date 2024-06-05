generate: genkey
	@./genkey $(ARGS)

crack: cr
	@./cr $(ARGS)

encrypt: en
	@./en $(ARGS)

decrypt: de
	@./de $(ARGS)

de:
	@g++ decrypt_message.cpp -o de -lgmp -lgmpxx

en:
	@g++ encrypt_message.cpp -o en -lgmp -lgmpxx

cr:
	@g++ crack_message.cpp -o cr -lgmp -lgmpxx

genkey:
	@g++ create_keys.cpp -o genkey -lgmp -lgmpxx

clean:
	@rm -f genkey de en cr a.out
