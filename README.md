# Brutus Encryption

Custom symmetric encryption tool written for fun with the goal of being simple and at least, nominally robust against frequency checks and dictionary attacks, while keeping the size ratio between original and encrypted data at 1.

## About Brutus

### Name

Named after Marcus Iunius Brutus for fighting against the tyranny of established encryption algorithms... Ok... The real reason for this name is that\
 **Brutus should not be trusted**.

### Safety

Brutus was written solely for fun and as such is **not safe at all**. It was tested only against simple frequency analysis and the dictionary attack with words contained in `dict.txt`.

### Necessary files

For simple text message encryption Brutus uses `charset.txt` also included in the repository. All tests were conducted on this version of the file, however in theory it's possible to create a completely custom `charset.txt`. For file encryption Brutus uses programmed-in `charset` containing characters necessary for hexadecimal values. If `charset.txt` is missing, Brutus will use basic programmed-in charset.

## License

Brutus is under [Apache 2.0](LICENSE.md) license and [Common Clause](NOTICE.md).

### Commercial use

Really? If you want to use Brutus commercially, know that, as stated in [NOTICE](NOTICE.md), **you are not allowed**, and actually you should rethink your security practices.
