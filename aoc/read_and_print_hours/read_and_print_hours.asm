.data
	hours:   .asciiz "\nEntre com as horas: "
	minutes: .asciiz "\nEntre com os minutos: "
	seconds: .asciiz "\nEntre com os segundos: "
	
	error_hours:   .asciiz "Valor inválido para as horas. Esperado número entre 0 e 23.\n"
	error_minutes: .asciiz "Valor inválido para os minutos. Esperado número entre 0 e 59.\n"
	error_seconds: .asciiz "Valor inválido para os segundos. Esperado número entre 0 e 59.\n"
	
	horary: .asciiz "\nHorário digitado: "
	
	colon: .asciiz ":"
	
.text

	Hours:
		li $v0,4      
		la $a0,hours  # Imprime mensagem solicitando as horas
		syscall
	
		li $v0,5      # Lê um inteiro do usuário
		syscall
	
		move $t0,$v0  # Move o valor lido para um reg temporário

		slti $t3,$t0,0     # Seta $t3 se o número lido for menor que zero (ou seja, um número inválido)
		slti $t4,$t0,24    # Seta $t4 se o número lido for menor que 60 (ou seja, um número válido)
		
		# Note que se os registradores $t3 e $t4 se encontrarem com os mesmos valores, quer dizer que 
		# o valor é inválido, pois ou o número será menor que zero, ou terá de ser maior que 24.
		
		beq $t3,$t4,InvalidHour   # Se $t3 for igual a $t4, é chamada a mensagem de erro correspondente
				
		j Minutes  # O valor estando correto, o programa passa para a leitura dos minutos
		
	# A leitura dos minutos e segundos são análogas a leitura das horas
		
	Minutes:
		li $v0,4        
		la $a0,minutes 
		syscall
		
		li $v0,5 
		syscall
		
		move $t1,$v0
		
		slti $t3,$t1,0    
		slti $t4,$t1,60   
		
		beq $t3,$t4,InvalidMinute		
		j Seconds
		
	Seconds:
		li $v0,4
		la $a0,seconds 
		syscall
		
		li $v0,5 
		syscall
		
		move $t2,$v0 
		
		slti $t3,$t2,0
		slti $t4,$t2,60
		
		beq $t3,$t4,InvalidSecond 
		
		j Print
		
	InvalidHour:
		li $v0,4
		la $a0,error_hours # Imprime a mensagem de erro
		syscall 
		
		j Hours # Realiza a leitura novamente das horas, até que ela seja válida
		
	# A mensagem de erro dos minutos e segundos são análogas as horas
	
	InvalidMinute:
		li $v0,4
		la $a0,error_minutes 
		syscall 
		
		j Minutes
		
	InvalidSecond:
		li $v0,4
		la $a0,error_seconds
		syscall 
		
		j Seconds
	
		 
	Print:
		li $v0,4
		la $a0,horary # Imprime a mensagem de horário
		syscall
	
		slti $t4, $t0, 10  # Se o número for menor que 10, é acrescentado um zero a esquerda
		beq $t4,$zero, L1
	        jal PrintZeroLeft
	        
	    L1: li $v0,1
		move $a0,$t0 # Imprime a hora lida
		syscall
		
		li $v0,4
		la $a0,colon # Imprime os dois pontos
		syscall
		
		slti $t4, $t1, 10
		beq $t4,$zero, L2
		jal PrintZeroLeft 
		
	    L2: li $v0,1
		move $a0,$t1 # Imprime os minutos lidos
		syscall
		
		li $v0,4
		la $a0,colon # Imprime os dois pontos
		syscall
		
		slti $t4, $t2, 10
		beq $t4,$zero, L3
		jal PrintZeroLeft
		
	    L3: li $v0,1
		move $a0,$t2 # Imprime os segundos lidos
		syscall
		
		j Exit
		
	PrintZeroLeft:
		li $v0,1
		la $a0,($0) # Imprime o número zero
		syscall
		jr $ra # Retorna a chamada da função
	
	Exit: 
	