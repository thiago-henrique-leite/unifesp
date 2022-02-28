package JavaProjects.vetores_colecoes_estDados.ex7;

//Mostre as saídas que seriam produzidas pelas chamadas imprimeAlgo(0), imprimeAlgo(1),
//imprimeAlgo(2), e imprimeAlgo(3).

public class ImprimeAlgo {
	static void imprimeAlgo(int nivel) {
		if (nivel == 0) {
			System.out.print("*");
	  } else {
			System.out.print("[");
			imprimeAlgo(nivel - 1);
			System.out.print(",");
			imprimeAlgo(nivel - 1);
			System.out.print("]");
		}
	}
	
	public static void main(String args[]) {
		System.out.println("\nImprimeAlgo(0):");
		imprimeAlgo(0);
		
		System.out.println("\nImprimeAlgo(1):");
		imprimeAlgo(1);
		
		System.out.println("\nImprimeAlgo(2):");
		imprimeAlgo(2);
		
		System.out.println("\nImprimeAlgo(3):");
		imprimeAlgo(3);
	}
}
