package JavaProjects.vetores_colecoes_estDados.ex3;

//Escreva um método nesta classe que, dado um vetor de funcionários e um número X de anos (os
//parâmetros do método), imprima o nome, sobrenome e salário de cada funcionário do vetor que
//esteve na empresa por X anos ou mais.

public class Funcionario {
	private String sobreNome;
	private String nome;
	private double salarioHora;
	private int anosNaEmpresa;
	
	public Funcionario(String nome, String sobreNome, double salarioHora, int anosNaEmpresa) {
		setNome(nome); setSobreNome(sobreNome); setSalarioHora(salarioHora); setAnosNaEmpresa(anosNaEmpresa);
	}
	
	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public void setSalarioHora(double salarioHora) {
		this.salarioHora = salarioHora;
	}
	
	public void setAnosNaEmpresa(int anosNaEmpresa) {
		this.anosNaEmpresa = anosNaEmpresa;
	}
	
	public void setSobreNome(String sobreNome) {
		this.sobreNome = sobreNome;
	}
	
	public String getNome() { return nome; }
	public double getSalarioHora() { return salarioHora; }
	public int getAnosNaEmpresa() {	return anosNaEmpresa; }
	public String getSobreNome() { return sobreNome; }
	
	public static void esteve_na_empresa_por_x_anos(Funcionario[] funcs, int x) {
		for( Funcionario func : funcs )
			if(func != null && func.getAnosNaEmpresa() >= x)
				System.out.println(func.toString());
	}
	
	public String toString() {
		return "Nome: " + nome + " " + sobreNome + " - " +
				"Salário p/hora: " + salarioHora + " - " +
				"Anos na empresa: " + anosNaEmpresa;
	}
	
	public static void main(String args[]) {
		Funcionario[] funcs = new Funcionario[100];
		
		funcs[0] = new Funcionario("Joao", "Silva", 12, 3);
		funcs[1] = new Funcionario("Pedro", "Henrique", 25, 6);
		funcs[2] = new Funcionario("Josias", "Ferreira", 32, 14);
		funcs[3] = new Funcionario("Juliete", "Cardoso", 69, 17);
		funcs[4] = new Funcionario("Sara", "Costa", 120, 13);
		funcs[5] = new Funcionario("Josimeire", "Rocha", 100, 18);
		funcs[6] = new Funcionario("Ricardo", "Pereira", 56, 7);
		funcs[7] = new Funcionario("Mario", "Quintana", 48, 15);
		funcs[8] = new Funcionario("Cristiana", "Ronalda", 72, 11);
		funcs[9] = new Funcionario("Polho", "Delari", 110, 12);
				
		System.out.println("Valor X: 10\n");
		esteve_na_empresa_por_x_anos(funcs, 10);
						
		System.out.println("\nValor X: 15\n");
		esteve_na_empresa_por_x_anos(funcs, 15);
	}
}
