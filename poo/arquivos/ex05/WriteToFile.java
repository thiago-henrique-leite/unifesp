package JavaProjects.arquivos.ex05;

import java.util.Map;

public class WriteToFile {
	
	public static void perform(Map<String, Integer> mapaPalavras, String arq) {
		Object[] palavras = mapaPalavras.keySet().toArray();
		Object[] numeros = mapaPalavras.values().toArray();
		
		String texto="", p="";
		
		for(int i=0; i<palavras.length; i++) {
			p = (String) palavras[i] + " " + numeros[i] + '\n';
			texto = texto + p;
		}
		
		writeInFile(texto, arq);
	}
	
	private static void writeInFile(String texto, String arquivo) {
		if(Arquivo.Write(arquivo, texto))
			System.out.println("Mapa de palavras salvo no arquivo " + arquivo + " com sucesso!");
		else
			System.err.println("Falha ao escrever no arquivo!");
	}
	
	public static void main(String[] args) {
		ListaDePalavras lista = new ListaDePalavras();
	    
		lista.add("João");
		lista.add("Maria");
		lista.add("Claudinei");
		lista.add("Maria");
		lista.add("João");
		lista.add("José");
		lista.add("Maria");
		lista.add("Paulo");
		
		MapPalavraContador m = new MapPalavraContador(lista);
		
		WriteToFile.perform(m.getMapaPalavras(), "target.txt");
	}
}
