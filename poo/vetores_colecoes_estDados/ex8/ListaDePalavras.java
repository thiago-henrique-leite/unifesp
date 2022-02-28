package JavaProjects.vetores_colecoes_estDados.ex8;

import java.util.*;

public class ListaDePalavras {
	protected Set<String> lista;
	public ListaDePalavras() {
		lista = new TreeSet<String>();
	}
	
	public void adiciona(String palavras) {
		StringTokenizer st = new StringTokenizer(palavras);
		while(st.hasMoreTokens())
			lista.add(st.nextToken());
	}

	public boolean existe(String palavra) {
		return lista.contains(palavra);
	}
}