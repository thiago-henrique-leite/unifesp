package JavaProjects.arquivos.ex01;

import java.io.IOException;
import java.util.StringTokenizer;
import java.util.Scanner;

//Método Sensitive Case

public class ContaCaracteres {
	
	public static int perform(String arq, char c) {
		StringTokenizer text = new StringTokenizer(arq);
		String word = "";
		int cont=0;
		
		while(text.hasMoreTokens()) {
			word = text.nextToken();
			word = word.replace(",", "").replace(".", "");
			
			for(int i=0; i<word.chars().count(); i++) 
				if(word.charAt(i)== c)
					cont++;
		}
		
		return cont;
	}
	
	public static void main(String[] args) throws IOException {
		Scanner read = new Scanner(System.in);
		
		System.out.print("Insira o nome do arquivo: ");
		String arq = read.nextLine();
		System.out.print("\nInsira o caracter para saber sua ocorrência: ");
		char caracter = read.nextLine().toCharArray()[0];
		
		String texto = Arquivo.Read(arq);
		
		if(texto.isEmpty()) {
			System.err.println("Falha ao ler do arquivo!");
		} else {
			System.out.println(texto);
			System.out.println("Ocorrências da letra '" + caracter + "': " + ContaCaracteres.perform(texto, caracter));
		}
				
		read.close();
	}

}
