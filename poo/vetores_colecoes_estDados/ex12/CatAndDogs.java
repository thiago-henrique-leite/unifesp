package JavaProjects.vetores_colecoes_estDados.ex12;

import java.util.ArrayList;
import java.util.List;

public class CatAndDogs {
	public static void main(String[] args) {
		List<Object> cats = new ArrayList<Object>();
		
		for(int i = 0; i < 7; i++)
			cats.add(new Cat(i));
		
		cats.add(new Dog(7));
		
		for(int i = 0; i < cats.size(); i++) {
			switch(cats.get(i).getClass().getSimpleName()) {
			case "Dog":
				((Dog) cats.get(i)).id();
				break;
			case "Cat":
				((Cat)cats.get(i)).id();
				break;
			default:
				break;
			}
		}
	}
}
