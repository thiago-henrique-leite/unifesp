package JavaProjects.vetores_colecoes_estDados.ex5;

//Qual é a saída do seguinte trecho de código?

public class Output {
	public static void main(String args[]) {
		char[][] pic = new char[6][6];
		
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++) {
					if ( i == j || i == 0 || i == 5 )
						pic[i][j] = '*';
					else
						pic[i][j] = '.';
			}
		
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++)
				System.out.println(pic[i][j]);
				
			System.out.println();
		}
	}
}
