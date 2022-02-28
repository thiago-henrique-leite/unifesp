package JavaProjects.arquivos.ex05;

import java.util.HashMap;
import java.util.Map;

public class MapPalavraContador {
	private ListaDePalavras palavras = new ListaDePalavras();
	private Map<String, Integer> mapaPalavras;
	
	public MapPalavraContador(ListaDePalavras palavras) {
		this.palavras = palavras;
		this.mapaPalavras = new HashMap<String, Integer>();
		perform();
	}
	
	public Map<String, Integer> getMapaPalavras() {
		return mapaPalavras;
	}
	
	public void perform() {
		for(String palavra : palavras.getLista())
			mapaPalavras.put(palavra, palavras.ocurrences(palavra));
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
				
		System.out.println(m.getMapaPalavras());
	}
}
