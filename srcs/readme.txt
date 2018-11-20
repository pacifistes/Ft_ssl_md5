MD5 :
    final String : 128 bits (4 x 32) // int[4] or char[4][4]
    block        : 512 (16 x 32 bits) // int[16] or char[16][4]
    
    Creation :
        split en block de 512 // (char[16][4])
        ajoute 1 a la fin du message
        ajoute des 0 jusqu'a atteindre un block de 448 bits (creation d'un new block if need)
        ajoute taille du message sur 64bits (long)

SHA ;
    final String : 256 bits
    block        : 512

Whirepool :
    final String : 512 bits
    block        : 512

