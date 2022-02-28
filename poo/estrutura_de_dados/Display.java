package JavaProjects.estrutura_de_dados;

import java.util.InputMismatchException;
import java.util.Scanner;

public class Display {	
	public static void invalidResponse() {
		System.out.println("Resposta inválida!");
	}
	
	public static void lineBreak() {
		System.out.println("______________________________________________________");
	}
	
	public static void end() {
		lineBreak();
		System.out.println("\nAté mais!");
	}
	
	public static void startMenu() {
		lineBreak();
		System.out.println("\n(1) Lista");
		System.out.println("(2) Pilha");
		System.out.println("(3) Fila");
		System.out.println("(4) Sair");
		System.out.print("\n>> ");	
  }
  
	public static void menu() {
		System.out.println("(1) Inserir");
		System.out.println("(2) Retirar");
		System.out.println("(3) Buscar");
		System.out.println("(4) Imprimir");
		System.out.println("(5) Voltar");
		System.out.print("\n>> ");
	}
	
	public static void main(String args[]) {
		Scanner ler = new Scanner(System.in);
		
		boolean end = false, back = false;
		String response, option;
		int n=0, pos=0;
		
		Lista lista = new Lista();
		lista.initiate();
		
		Pilha pilha  = new Pilha();
		pilha.initiate();

		Fila fila = new Fila();
		fila.initiate();
		
		
		while(!end) {
			try {
				startMenu();
				option = ler.nextLine();
				switch(option) {
				case "1":
					back = false;
					while(!back) {
						lineBreak();
            System.out.println("\t\tManipule sua Lista\n");
						menu();
						response = ler.nextLine();
						switch(response) {
						case "1":
							lineBreak();
							System.out.print("\nDigite a chave de inserção e a posição: ");
							n = ler.nextInt();
							pos = ler.nextInt();
							
							ler.nextLine();
							
							lineBreak();
							if(lista.validPosition(pos)) {
								lista.add(n, pos);
								System.out.printf("\nChave %d inserida com sucesso!\n", n);
							}
							else {
								System.out.println("\nPosição inválida!");
								System.out.printf("Posição deve estar no intervalo (1..%d).\n", lista.getLength()+1);
							}
							break;
						case "2":
							lineBreak();
							if(lista.isEmpty()) {
								System.out.println("\nLista está vazia.");
							} else {
								System.out.print("\nDigite a chave de remoção: ");
								n = ler.nextInt();
								ler.nextLine();
								lineBreak();
								if(lista.remove(n)==1)
									System.out.printf("\nChave %d removida da lista!\n", n);
								else 
									System.out.println("\nChave não existe!");
							}
							break;
						case "3":
							lineBreak();
							System.out.print("\nDigite a chave de busca: ");
							n = ler.nextInt();
							ler.nextLine();
							lineBreak();
							if(lista.search(n)==null)
								System.out.println("\nChave não existe!");
							else 
								System.out.printf("\nChave %d encontrada na lista!\n", n);
							break;
						case "4":
							lineBreak();
							lista.print();
							break;
						case "5":
							back = true;
							break;
						default:
							lineBreak();
							invalidResponse();
							break;
						}
					}
					break;
				case "2":
					back = false;
					while(!back) {
						lineBreak();
            System.out.println("\t\tManipule sua Pilha\n");
						menu();
						response = ler.nextLine();
						switch(response) {
						case "1":
							lineBreak();
							System.out.print("\nDigite a chave de inserção: ");
							n = ler.nextInt();
							
							ler.nextLine();
							
							lineBreak();
							pilha.add(n);
							System.out.printf("\nChave %d inserida com sucesso!\n", n);
							break;
						case "2":
							lineBreak();
							if(pilha.isEmpty()) {
								System.out.println("\nPilha está vazia.");
							} else {
								n = pilha.getFirst().getKey();
								pilha.remove();
								System.out.printf("\nChave %d removida da pilha!\n", n);
							}
							break;
						case "3":
							lineBreak();
							System.out.print("\nDigite a chave de busca: ");
							n = ler.nextInt();
							ler.nextLine();
							lineBreak();
							if(pilha.search(n)==null)
								System.out.println("\nChave não existe!");
							else 
								System.out.printf("\nChave %d encontrada na pilha!\n", n);
							break;
						case "4":
							lineBreak();
							pilha.print();
							break;
						case "5":
							back = true;
							break;
						default:
							lineBreak();
							invalidResponse();
							break;
						}
					}
					break;
				case "3":
					back = false;
					while(!back) {
						lineBreak();
            System.out.println("\t\tManipule sua Fila\n");
						menu();
						response = ler.nextLine();
						switch(response) {
						case "1":
							lineBreak();
							System.out.print("\nDigite a chave de inserção: ");
							n = ler.nextInt();
							
							ler.nextLine();
							
							lineBreak();
							fila.add(n);
							System.out.printf("\nChave %d inserida com sucesso!\n", n);
							break;
						case "2":
							lineBreak();
							if(fila.isEmpty()) {
								System.out.println("\nFila está vazia.");
							} else {
								n = fila.getFirst().getKey();
								fila.remove();
								System.out.printf("\nChave %d removida da fila!\n", n);
							}
							break;
						case "3":
							lineBreak();
							System.out.print("\nDigite a chave de busca: ");
							n = ler.nextInt();
							ler.nextLine();
							lineBreak();
							if(fila.search(n)==null)
								System.out.println("\nChave não existe!");
							else 
								System.out.printf("\nChave %d encontrada na fila!\n", n);
							break;
						case "4":
							lineBreak();
							fila.print();
							break;
						case "5":
							back = true;
							break;
						default:
							lineBreak();
							invalidResponse();
							break;
						}
					}
					break;
				case "4":
					end();
					end = true;
					break;
				}
			} catch(InputMismatchException e) {
				System.out.println("\nOperação não concluída. Valor lido inválido.");
				ler.nextLine();
			} catch(NullPointerException e2) {
				System.out.println("\nOperação não concluída. Objeto nulo.");
				ler.nextLine();
			}
		}
		ler.close();
	}
}