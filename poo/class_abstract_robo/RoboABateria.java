package JavaProjects.class_abstract_robo;

public class RoboABateria extends RoboAbstrato {
	protected long energia;
	
	public RoboABateria(String n, int px, int py, short d, long e) {
		super(n, px, py, d);
		energia = e;
	}
	
	public boolean ehDiagonal() {
		int n = direcaoAtual();
		// Se n é ímpar, múltiplo de 45 e está entre 44 e 136, o movimento é diagonal
		return (n >= 45 && n < 315 && n%2 != 0 && n%45 == 0) ? true : false; 
	}
	
	public void move(int passos) {
		long energiaASerGasta = passos * ( (ehDiagonal()) ? 14 : 10);
		
		if (energiaASerGasta <= energia) {
			switch (direcaoAtual()) {
			case 0:
				moveX(+passos);
				break;
			case 45:
				moveX(+passos);
				moveY(+passos);
				break;
			case 90:
				moveY(+passos);
				break;
			case 135:
				moveY(+passos);
				moveX(-passos);
				break;
			case 180:
				moveX(-passos);
				break;
			case 225:
				moveX(-passos);
				moveY(-passos);
				break;
			case 270:
				moveY(-passos);
				break;
			case 315:
				moveY(-passos);
				moveX(+passos);
				break;
			}
			energia -= energiaASerGasta;
		}
	}
	
	public String toString() {
		String resultado = super.toString() + "\n";
		resultado = resultado + "Energia do robô:" + energia;
		return resultado;
	}
	
	public void recarrega(int carga) {
		this.energia += carga;
	}
}