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


int			main(int ac, char **av)
{
	int i;
	// t_manager manager;
	// if (!init_manager(&manager, ac, av))
	// {
	// 	ft_printf("Error in parameters, usage: ");
	// 	ft_printf("./ft_ssl sha256|md5 [-pqhr] [-s string ...] [file ...]");
	// 	return (1);
	// }
	// execute(&manager);


	(void)ac;
	(void)av;
	i = 0;
	t_block block;
	int j;
	uint32_t plop[16];
	while (i < 16)
	{
		j = 0;
		block.words[i] = 0;
		plop[i] = 0;
		while (j < 32)
		{
			block.words[i] |= 0 << j;
			j++;
		}
		if (i == 0)
		{
		}
		// ft_printf("%x\n", block.words[i]);
		print_memory_hex(&block.words[i], sizeof(u_int32_t));
		i++;
	}
	// block.words[0] = 1;
	// block.words[15] |= 1 << 0;

	// ft_printf("%x\n", words.a);
	i = 0;
		t_hash_md5_word words;
	while (i < 32)
	{
		block.words[0] |= (1 << i);
		words = md5_loop(block);
		plop[0] |= (1 << i);
		algo(plop, 10);
		block.words[0] &= ~(1 << i);
		plop[0] &= ~(1 << i);
		ft_printf("le miens :%x%x%x%x\n", words.a, words.b, words.c, words.d);
		i++;
	}

	// t_datas *datas;
	// datas = manager.datas;
	// ft_printf("%b\n", manager.options);
	// while (datas)
	// {
	// 	if (datas->is_file)
	// 		ft_printf("{%s} is a file\n", datas->str);
	// 	else
	// 		ft_printf("{%s} is string\n", datas->str);
	// 	datas = datas->next;
	// }
	return (0);
}
