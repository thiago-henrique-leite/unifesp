package JavaProjects.vetores_colecoes_estDados.ex1;

import java.util.InputMismatchException;
import java.util.Scanner;

/* 
   Escreva um programa que lê uma sequência de números positivos dada pelo usuário e imprima
   os mesmos números ordenados ascendentemente. O usuário entrará com 0 para marcar o fim da
   entrada. Assuma que no máximo 100 números serão lidos. 
*/

public class ReadNumbers {
	public static int[] quicksort(int[] vet, int p, int r) {
		int q;
	    if(p<r) {
	        q = partition(vet, p, r); 
	        quicksort(vet, p, q-1); 
	        quicksort(vet, q+1, r); 
	    }
	    
		return vet;
	}
	
	public static int partition(int vet[], int p, int r) { 
	    int i, j;
	    i = p;
	    for(j=p; j<r; j++) { 
	        if(vet[j] <= vet[r]) { 
	            swap(vet, i, j);
	            i++;
	        }
	    }
	    swap(vet, i, r); 
	    return(i); 
	}
	
	public static void swap(int vet[], int x, int y) { 
	    if(x!=y) {
	        int aux; 
	        aux = vet[x];
	        vet[x] = vet[y];
	        vet[y] = aux;
	    }
	}
	
	public static int read_numbers(int[] vet) {
		Scanner read = new Scanner(System.in);
		
		int n, ind=0, tam=0;
		boolean fim=false;
		
		for(int i=0; i<100 && !fim; i++) {
			n = read.nextInt();
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
	
	public static void print(int[] vet, int tam) {
		int i;
		
		for(i=0; i<tam; i++) {
			System.out.printf("%d\n", vet[i]);
		}
	}
	
	public static void main(String args[]) {
		int[] vet = new int[100];
		int tam=0;
		
		try {
			tam = read_numbers(vet);
		} catch(InputMismatchException e) {
			System.err.println("Caracter lido inválido!");
		}
		
		vet = quicksort(vet, 0, tam-1);
		
		print(vet, tam);
		
	}
}
