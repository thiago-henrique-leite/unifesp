package JavaProjects.vetores_colecoes_estDados.ex8;

// Escreva uma classe ContadorDePalavras baseada na classe ListaDePalavras abaixo que, além de armazenar palavras, 
// armazene também quantas vezes uma palavra foi armazenada. Escreva métodos para essa classe que recuperem o número 
// de vezes que uma palavra foi armazenada ou zero se ela não tiver sido armazenada.

// Set não permite elementos duplicados

public class ContadorDePalavras extends ListaDePalavras {
	public ContadorDePalavras() {
		super();
	}
	
	public int ocorrencias(String key) {
		int cont=0;
		
		for(String palavra : lista) {
			if(palavra.equals(key)) { cont++; }
		}
		
		return cont;
	}
	
	public static void main(String[] args) {
		ContadorDePalavras cont = new ContadorDePalavras();
		
		cont.adiciona("Quando digo digo digo digo não digo Diogo Quando digo diogo digo diogo não digo digo");
		
		System.out.println("A palavra 'digo' existe? " + cont.existe("digo"));
		System.out.println("Quantidade de vezes que a palavra 'digo' aparece: " + cont.ocorrencias("digo"));
		System.out.println("Quantidade de vezes que a palavra 'cordialmente' aparece: " + cont.ocorrencias("cordialmente"));
	}
}
