.data	 
	ArrayDeChars:	    .space 4000         # Vetor com os caracteres lidos
	ArrayDeEnd: 	    .space 4000           # Vetor com o endereço do início de cada palavra
	ArrayDePalavrasRep: .space 4000   # Vetor com as palavras repetidas
	ArrayAux: 	    .space 4000             # Vetor auxiliar para guardar o endereço das palavras repetidas.
	
	msg1:   .asciiz "\nEntre com uma frase: "
	msg2:   .asciiz "\nNúmero total de caracteres: "
	msg3:   .asciiz "\nNúmero total de palavras: "
	msg4:   .asciiz "Palavras repetidas: "
	barraN: .asciiz "\n"

.text

Main:
	# Imprime mensagem inicial
	li $v0, 4 
	la $a0, msg1
	syscall
	
	li $s6, 0 # Zera contador de caracteres
	li $s7, 0 # Zera contador de palavras
	li $t0, 0 # Zera $t0
	
	li $t2, 0 # Zera indice do vetor de caracteres
	li $t3, 0 # Zera indice do vetor de palavras
	li $t4, 0
	
ReadText:
	add $t1, $t0, $zero # $t1 recebe o caracter anterior
   	
	li $v0, 12 # Le caracter
	syscall
	
	move $t0,$v0 # Salva ele em $t0
	
	beq $t0, 10, ImprimeResultados # Se o caracter for <enter> sai do loop

	beq $t0, 32, IncrementaChar # Se o caracter for <space> não é uma nova palavra
	
	bltu $t0, 65, IncrementaChar # Verifica se o caracter não é símbolo ou número
	
	VerificaSeCaracterEhValido:
	
		sltiu $a0, $t0, 97
		sgtu $a1, $t0, 90
		beq $a0, $a1, IncrementaChar
	
		sgtu $a1, $t0, 122
		sltiu $a0, $t0, 128
		beq $a0, $a1, IncrementaChar
	
		sgtu $a1, $t0, 154
		sltiu $a0, $t0, 159
		beq $a0, $a1, IncrementaChar
	
		sgtu $a1, $t0, 154
		sltiu $a0, $t0, 159
		beq $a0, $a1, IncrementaChar
	 
		beq $s6, 0, IncrementaPalavra # Se é o primeiro caracter lido salvamos a primeira palavra
	
		bne $t1, 32, IncrementaChar # Se o caracter anterior não for espaço, não é uma nova palavra 
	
	IncrementaPalavra:
		# Incrementa vetor de palavras e grava a primeira letra no vetor
		addi $s7, $s7, 1
		
		sw $t4, ArrayDeEnd($t3)
		addi $t3, $t3, 4
	
	IncrementaChar:		
		# Incrementa vetor de caracteres e grava ele no vetor
		addi $s6, $s6, 1
		
		sw $t0, ArrayDeChars($t2)
		addi $t2, $t2, 4
		addi $t4, $t4, 4
		
	j ReadText

ImprimeResultados:
	#Adiciona espaço no final do array de chars
	li $t0, 10 
	sw $t0, ArrayDeEnd($t3)
	
	#Adiciona espaço no final do array de chars
	li $t0, 32 
	sw $t0, ArrayDeChars($t2)
	
	#Imprime quantidade de caracteres e quantidade de palavras
	li $v0, 4
	la $a0, msg2
	syscall
	
	li $v0, 1
	la $a0, ($s6)
	syscall
	
	li $v0, 4
	la $a0, msg3
	syscall
	
	li $v0, 1
	la $a0, ($s7)
	syscall
	
	li $v0, 4
	la $a0, barraN
	syscall
	
	li $t0, 0
	li $t1, 0
	
EncontraPalavraRepitida:
	li $t0, 0 # Índice do array de endereços
		
	li $s5, 0 # Indice do vetor ArrayDePalavrasRep
	li $s6, 0 # Indice do vetor ArrayAux
	
	li $t9, 0 # Contador de palavras repetidas
	li $s4, 1 # Contador de palavras
	
	beq $t3, $zero, End # Se o número de palavras for zero o programa terminou
	
	ForExterno:
		lw $t5, ArrayDeEnd($t0)
		
		lw $s0, ArrayDeChars($t5)
			
		beq $s4, $s7, ImprimePalavrasRepetidas
		
		addi $t1, $t0, 4
		
		ForInterno: 
			lw $t6, ArrayDeEnd($t1)
			
			beq $t6, 10, EndForExterno
			
			lw $s1, ArrayDeChars($t6)

			bne $s0, $s1, EndForInterno
			
			add $t2, $t5, $zero
			add $t3, $t6, $zero
			
			lw $s2, ArrayDeChars($t2)
			lw $s3, ArrayDeChars($t3)
			
			ComparaLetras:
				beq $s2, 32, PalavraEhRepetida
				bne $s2, $s3, EndForInterno
				
				addi $t2, $t2, 4
				addi $t3, $t3, 4
				
				lw $s2, ArrayDeChars($t2)
				lw $s3, ArrayDeChars($t3)
			
				beq $s2, $s3, ComparaLetras
				
				j EndForInterno
			
			PalavraEhRepetida:
 				bne $s3, 32, EndForInterno
 				
 				verifica_se_palavra_ja_foi_adicionada:
 					beq $t9, 0, addArray
 					
 					li $t7, 0
 					li $a2, 0
 					
 					for_each:			
 						lw $a1, ArrayAux($t7)
						
 						beq $t5, $a1, addArrayAux
 						
 						beq $a2, $t4, addArray
 						
 						addi $t7, $t7, 4
 						addi $a2, $a2, 1
 						
 						j for_each
 				
 				addArray:
					bne $s3, 32, EndForInterno
 				
					sw $t6, ArrayDePalavrasRep($s5)
		
					addi $s5, $s5, 4
					addi $t9, $t9, 1
				
					sw $t5, ArrayAux($s6)
					addi $s6, $s6, 4
					sw $t6, ArrayAux($s6)
					addi $s6, $s6, 4
			
					j EndForExterno
			
				addArrayAux:
					sw $t5, ArrayAux($s6)
					addi $s6, $s6, 4
					sw $t6, ArrayAux($s6)
					addi $s6, $s6, 4
			
					addi $t4, $t4, 2
			
					j EndForInterno
			
		EndForInterno:
			addi $t1, $t1, 4

			j ForInterno
		
	EndForExterno:
		addi $t0, $t0, 4
		addi $s4, $s4, 1
		j ForExterno
		
	

ImprimePalavrasRepetidas:
	li $t0, 0
	li $t8, 0 # Conta quantas palavras já foram impressas
		
	li $v0, 4
	la $a0, msg4
	syscall
	
	beqz $t9, End
	
	For:
		beq $t8, $t9, End
		
		lw $t1, ArrayDePalavrasRep($t0)
		
		lw $s0, ArrayDeChars($t1)
		
		ImprimeLetras:
			beq $s0, 32, EndImprimeLetras 	
			
			li $v0, 11
			la $a0, ($s0)
			syscall
			
			addi $t1, $t1, 4
			
			lw $s0, ArrayDeChars($t1)
			
			j ImprimeLetras
			
		EndImprimeLetras:
			li $t4, 32
			
			li $v0, 11
			la $a0, ($t4)
			syscall
			
			addi $t0, $t0, 4
			addi $t8, $t8, 1
			j For
		

End:
	li $t4, 10
			
	li $v0, 11
	la $a0, ($t4)
	syscall
	
