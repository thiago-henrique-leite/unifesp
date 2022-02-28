package JavaProjects.vetores_colecoes_estDados.ex2;

import java.util.InputMismatchException;
import java.util.Scanner;

// Escreva um programa que, dado um vetor de doubles, retorna a média dos números no vetor.
// Critério de parada de leitura é o número 0

public class Average {
	private double[] vet = new double[100];
	private double media;
	
	public Average(double vet[], int length) {
		this.vet = vet;
		calculate_media(vet, length);
	}
	
	public double[] getVet() {
		return this.vet;
	}
	
	public double getMedia() {
		return this.media;
	}
	
	public void calculate_media(double vet[], int length) {
		double soma=0;
		
		for(int i=0; i<length; i++) {
			soma += vet[i];
		}
		
		this.media = soma/length;
	}
	
	public static int read_numbers(double[] vet) {
		Scanner read = new Scanner(System.in);
		
		boolean fim=false;
		int ind=0, tam=0;
		double n;
		
		for(int i=0; i<100 && !fim; i++) {
			n = read.nextDouble();
			if(n==0)
				fim=true;
			else {
				vet[ind] = n;
				ind++; tam++;
			}
		}
		
		read.close();
		return tam;
	}

	public static void main(String args[]) {
		double[] vet = new double[100];
		int tam=0;
		
		try {
			tam = read_numbers(vet);
			Average vetMedia = new Average(vet, tam);
			System.out.printf("A média dos números inseridos é: %.2f", vetMedia.getMedia());
		} catch(InputMismatchException e) {
			System.err.println("Caracter lido inválido!");
		}
	}
}
