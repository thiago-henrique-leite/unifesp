package JavaProjects.class_abstract_robo;

public class RoboSimples extends RoboAbstrato {
	public RoboSimples(String n, int px, int py, short d) {
		super(n, px, py, d);
	}
	
	public void move(int passos) {
		switch (direcaoAtual()) {
		case 0:
			moveX(+passos);
			break;
		case 90:
			moveY(+passos);
			break;
		case 180:
			moveX(-passos);
			break;
		case 270:
			moveY(-passos);
			break;
		}
	}

	public void mudaDirecao(short novaDir) {
		if(novaDir < 45 || novaDir > 315) 
			direcao = 0;
		else if(novaDir > 45 && novaDir < 135) 
			direcao = 90;
		else if(novaDir > 135 && novaDir < 225) 
			direcao = 180;
		else if(novaDir > 225 && novaDir < 315) 
			direcao = 270;
		else 
			direcao = novaDir;
	}
}