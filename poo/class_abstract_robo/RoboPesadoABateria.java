package JavaProjects.class_abstract_robo;

public class RoboPesadoABateria extends RoboABateria {
	private int peso;
	
	public RoboPesadoABateria(String n, int px, int py, short d, long e, int peso) {
		super(n, px, py, d, e);
		this.peso = peso;
	}
	
	public void move(int passos) {
		long energiaASerGasta = (long) (passos * peso * ((ehDiagonal()) ? 1.4 : 1));
		
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
		resultado = resultado + "Peso: " + peso + "kg";
		return resultado;
	}
}