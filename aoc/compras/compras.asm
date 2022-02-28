# Código produzido por Thiago Henrique Leite da Silva, Unifesp - RA: 139920

.data	 
	ArrayQuantidade:    .space 4000  
	ArrayValorTotal:    .space 4000          
	ArrayValorUnitario: .space 4000    
		
	produto1: .space 100
	produto2: .space 100
	produto3: .space 100
	produto4: .space 100
	produto5: .space 100 
	
	msg1:  .asciiz "\nDigite o nome do produto: "
	msg2:  .asciiz "Insira o valor unitário deste produto: "
	msg3:  .asciiz "Insira a quantidade desejada deste produto: "
	msg4:  .asciiz "\nDeseja comprar algo a mais? Se sim, digite 1. Caso contrário, digite 0. Resposta: "
	msg5:  .asciiz "\nPedido:"
	msg6:  .asciiz "x "
	msg7:  .asciiz "Valor unitário: R$ "
	msg8:  .asciiz "\nValor total do produto: R$ "
	msg9:  .asciiz "\n\nValor total do pedido: R$ "
	msg10: .asciiz "\n\n"
	
	cem: .float 100.0
	zero: .float 0.0
	
	tamanho: .space 100
	
.text

Start:
	li $s0, 0 # Indíce ArrayProdutos
	li $s1, 0 # Indíce ArrayValorUnitario
	li $s2, 0 # Indíce ArrayValorTotal
	li $s3, 0 # Indice ArrayQuantidade
	
	lwc1 $f4, zero # Valor total do pedido
	
	li $s5, 0 # Contador de produtos
 
Produto:

	li $v0, 4 
	la $a0, msg1
	syscall
	
	beq $s5, 0, Produto1
	beq $s5, 1, Produto2
	beq $s5, 2, Produto3
	beq $s5, 3, Produto4
	beq $s5, 4, Produto5

	Produto1:	
		li $v0, 8
		la $a0, produto1
		li $a1, 100
		syscall
		
		j ValorUnitario
	Produto2:	
		li $v0, 8
		la $a0, produto2
		li $a1, 100
		syscall
		
		j ValorUnitario
	Produto3:	
		li $v0, 8
		la $a0, produto3
		li $a1, 100
		syscall
		
		j ValorUnitario
	Produto4:	
		li $v0, 8
		la $a0, produto4
		li $a1, 100
		syscall
		
		j ValorUnitario
	Produto5:	
		li $v0, 8
		la $a0, produto5
		li $a1, 100
		syscall
		
		j ValorUnitario

ValorUnitario:
	
	li $v0, 4 
	la $a0, msg2
	syscall
	
	li $v0, 6
	syscall
	
	lwc1 $f1, zero
	add.s $f2, $f1, $f0
	
	swc1 $f2, ArrayValorUnitario($s1)
	addi $s1, $s1, 4

Quantidade:

	li $v0, 4 
	la $a0, msg3
	syscall
	
	li $v0, 5 
	syscall
	
	move $t7, $v0
	
	sw $t7, ArrayQuantidade($s2)
	addi $s2, $s2, 4
	
	mtc1 $t7, $f3
	cvt.s.w $f3, $f3
	
ValorTotal:
	mul.s $f7, $f2, $f3
	
	la $a0, cem
	l.s $f11, ($a0)
	mul.s $f7, $f7, $f11
	div.s $f7, $f7, $f11
	
	swc1 $f7, ArrayValorTotal($s3)
	addi $s3, $s3, 4
	
ValorPedido:

	add.s $f4, $f4, $f7
	
VerificaSeTerminou:
	
	addi $s5, $s5, 1
	beq $s5, 5, ImprimePedido

	li $v0, 4 
	la $a0, msg4
	syscall
	
	li $v0, 5
	syscall
	
	move $t0, $v0
	beq $t0, 1, Produto

ImprimePedido:

	li $s0, 0 
	li $s2, 0
	li $s4, 0
	
	li $v0, 4 
	la $a0, msg5
	syscall
	
ImprimeDadosProduto:

	beq $s4, $s5, ImprimeValorDoPedido
	
	li $v0, 4 
	la $a0, msg10
	syscall
	
	ImprimeQuantidade:
		lw $t0,  ArrayQuantidade($s0)
	
		li $v0, 1
		la $a0, ($t0)
		syscall
		
	ImprimeX:
		li $v0, 4 
		la $a0, msg6
		syscall
		
	ImprimeProduto:
	
		beq $s4, 0, PrintProduto1
		beq $s4, 1, PrintProduto2
		beq $s4, 2, PrintProduto3
		beq $s4, 3, PrintProduto4
		beq $s4, 4, PrintProduto5
		
		j ImprimeValorUnitário
		
		PrintProduto1:
			li $v0, 4
			la $a0, produto1
			syscall
			j ImprimeValorUnitário
		PrintProduto2:	
			li $v0, 4
			la $a0, produto2
			syscall
			j ImprimeValorUnitário
		PrintProduto3:	
			li $v0, 4
			la $a0, produto3
			syscall
			j ImprimeValorUnitário
		PrintProduto4:	
			li $v0, 4
			la $a0, produto4
			syscall
			j ImprimeValorUnitário
		PrintProduto5:	
			li $v0, 4
			la $a0, produto5
			syscall
			j ImprimeValorUnitário
		
	ImprimeValorUnitário:
	
		li $v0, 4 
		la $a0, msg7
		syscall
		
		lwc1 $f5, zero
		lwc1 $f6, ArrayValorUnitario($s0)
		
		add.s $f12, $f5, $f6
		
		li $v0, 2
		syscall
		
	ImprimeValorTotal:
		
		li $v0, 4 
		la $a0, msg8
		syscall
		
		lwc1 $f5, zero
		lwc1 $f6, ArrayValorTotal($s0)
		
		add.s $f12, $f5, $f6
		
		li $v0, 2
		syscall
	
	IncrementaContadores:	

		addi $s0, $s0, 4 
		addi $s4, $s4, 1
		
		j ImprimeDadosProduto
	
ImprimeValorDoPedido:
	li $v0, 4 
	la $a0, msg9
	syscall
	
	lwc1 $f5, zero
	
	add.s $f12, $f5, $f4
	
	lwc1 $f1, zero
	round.w.s $f1, $f12
	
	li $v0, 2
	syscall
	
	li $t0, 10
	li $v0, 11
	la $a0, ($t0)
	syscall
	
END:
