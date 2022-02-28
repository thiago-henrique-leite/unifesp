package JavaProjects.arquivos.ex04;

import java.util.*;

public class ListaDePalavras {
	protected ArrayList<String> lista;
	public ListaDePalavras() {
		lista = new ArrayList<String>();
	}
	
	public void add(String palavras) {
		StringTokenizer str = new StringTokenizer(palavras);
		while(str.hasMoreTokens())
			lista.add(str.nextToken());
	}

	public boolean existe(String palavra) {
		return lista.contains(palavra);
	}
	
	public ArrayList<String> getLista() {
		return lista;
	}
	
	public int ocurrences(String key) {
		int cont=0;
		
		for(String palavra : lista)
			if(palavra.equals(key)) { cont++; }
		
		return cont;
	}
}