package JavaProjects.arquivos.ex03;

import java.util.ArrayList;
import java.util.StringTokenizer;

// Classe que lê arquivos do tipo:
// UmaPalavra 13
// OutraPalavra 10

public class PalavraNumero {
	private static ArrayList<String> palavras = new ArrayList<String>();
	private static ArrayList<Integer> numeros = new ArrayList<Integer>();
	
	public PalavraNumero(String arquivo) {
		perform(Arquivo.Read(arquivo));
	}
	
	public ArrayList<Integer> getNumeros() { return numeros; }
	public ArrayList<String> getPalavras() { return palavras; }
	
	public static void perform(String arq) {
		StringTokenizer text = new StringTokenizer(arq);
		String word = "";

		while(text.hasMoreTokens()) {
			word = text.nextToken();
			palavras.add(word);
			
			word = text.nextToken();
			numeros.add(Integer.parseInt(word));
		}
	}
	
	public static void main(String[] args) {
		PalavraNumero pn = new PalavraNumero("palavra_num.txt");
		
		ArrayList<String> palavras = pn.getPalavras();
		ArrayList<Integer> numeros = pn.getNumeros();
		
		System.out.println("Palavras:\n");
		for(String palavra : palavras)
			System.out.println(palavra);
		
		System.out.println("\nNúmeros:\n");
		for(Integer n : numeros) 
			System.out.println(n);
	}
}
