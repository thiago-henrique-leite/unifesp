package JavaProjects.vetores_colecoes_estDados.ex4;

import java.util.InputMismatchException;
import java.util.Scanner;

//Escreva um método que encontra o maior inteiro de um vetor de inteiros.
// Critério de parada de leitura é o número 0

public class SearchMaxValue {
	private int maxValue;
	private int[] vet = new int[100];
	
	public SearchMaxValue(int[] vet) {
		setVet(vet);
		setMaxValue();
	}
	
	public int[] getVet() {
		return vet;
	}

	public void setVet(int[] vet) {
		this.vet = vet;
	}
	
	private void setMaxValue() {		
		if(vet != null)
			maxValue = vet[0];
		
		for( int n : vet ) 
			if(n > maxValue)
				maxValue = n;
	}
	
	public int getMaxValue() {
		return this.maxValue;
	}
	
	public static void read_numbers(int[] vet) {
		Scanner read = new Scanner(System.in);
		
		int n, ind=0;
		boolean fim=false;
		
		for(int i=0; i<100 && !fim; i++) {
			n = read.nextInt();
			if(n==0)
				fim=true;
			else {
				vet[ind] = n;
				ind++;
			}
		}
		
		read.close();
	}
	
	public static void main(String args[]) {
		int[] vet = new int[100];
		
		System.out.println("Entre com os valores do vetor:\n");
		
		try {
			read_numbers(vet);
		} catch(InputMismatchException e) {
			System.err.println("Caracter lido inválido!");
		}
		
		SearchMaxValue response = new SearchMaxValue(vet);
		
		System.out.printf("Valor máximo do vetor é: %d\n", response.getMaxValue());		
	}
}
