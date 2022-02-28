package JavaProjects.arquivos.ex02;

import java.util.Scanner;

public class CopiaArquivo {
	
	public static void main(String[] args) {
		Scanner read = new Scanner(System.in);
		
		System.out.print("Insira o nome do arquivo de origem: ");
		String origin = read.nextLine();
		
		System.out.print("Insira o nome do arquivo de destino: ");
		String target = read.nextLine();
		
		String texto = Arquivo.Read(origin);
		
		if(Arquivo.Write(target, texto))
			System.out.printf("\nArquivo %s copiado em %s\n", origin, target);
		else
			System.err.println("Falha ao gravar no arquivo.");
				
		read.close();
	}
}
