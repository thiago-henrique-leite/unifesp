import java.util.*;
import java.util.Map.Entry;
import java.util.stream.Stream;

public class KnnAlgorithm {
    private double[] attributeA1, attributeA2;
    private int[] classes;

    private TreeMap<Double, Integer> distanceClass;
    private TreeMap<Integer, Integer> classOccurrences;

    private final int K;
    private double a1, a2;

    public KnnAlgorithm(double[] a1, double[] a2, int[] classes, int k) {
        this.K = k;
        this.attributeA1 = a1;
        this.attributeA2 = a2;
        this.classes = classes;
        this.distanceClass = new TreeMap<>();
        this.classOccurrences = new TreeMap<>();
    }

    public void perform() {
        readInfoOfUser();
        train_with_euclidean_distance();
        train_with_manhattan_distance();
    }

    public void readInfoOfUser() {
        @SuppressWarnings("resource")
        Scanner read = new Scanner(System.in);

        System.out.println("Insira os atributos do elemento que deseja classificar:\n");
        
        System.out.print("Atributo A1: ");
        a1 = read.nextDouble();
        
        System.out.print("Atributo A2: ");
        a2 = read.nextDouble();
        
        System.out.println();
    }

    public void train_with_euclidean_distance() {
        clearHashs();
        System.out.println("Treinando algoritmo com distância euclideana:");
        printResult(classifyElement(a1, a2, "euclidean"));
    }

    public void train_with_manhattan_distance() {
        clearHashs();
        System.out.println("Treinando algoritmo com distância de manhattan:");
        printResult(classifyElement(a1, a2, "manhattan"));
    }

    public void clearHashs() {
        distanceClass.clear();
        classOccurrences.clear();
    }

    public int classifyElement(double a, double b, String distance_type) {
        Double distance=null;

        for(int i=0; i<classes.length; i++) {
            if(distance_type.equals("euclidean"))
                distance = euclideanDistance(i, a, b);
            else if(distance_type.equals("manhattan"))
                distance = manhattanDistance(i, a, b);

            distanceClass.put(distance, classes[i]);
        }
        
        Stream<Map.Entry<Double, Integer>> sortedMap = distanceClass.entrySet().stream().sorted(Map.Entry.comparingByKey()).limit(K);
        
        int element_class = getClassWithBiggerOccurrence(sortedMap);
        
        return element_class;
    }

    public int getClassWithBiggerOccurrence(Stream<Map.Entry<Double,Integer>> sortedMap) {
        Iterator<Entry<Double, Integer>> it = sortedMap.iterator();
        
        int countOne=0, countTwo=0;

        while(it.hasNext()) {
            if(it.next().getValue() == 1)
                countOne++;
            else
                countTwo++;
        }

        classOccurrences.put(1, countOne);
        classOccurrences.put(2, countTwo);

        return (countOne > countTwo) ? 1 : 2;
    }

    public Double euclideanDistance(int i, double a, double b) {
        return Math.pow(attributeA1[i] - a, 2) + Math.pow(attributeA2[i] - b, 2);
    }

    public Double manhattanDistance(int i, double a, double b) {
        return Math.abs(attributeA1[i] - a) + Math.abs(attributeA2[i] - b);
    }

    public void printResult(int element_class) {
        System.out.println("Espécie: " + element_class + " >> " + classOccurrences + "\n");
    }

    public static void main(String args[]) {
        double[] A1 = {0.5, 2.9, 1.2, 0.8, 2.7, 8.1, 8.3, 6.3, 8.0, 5.4};
        double[] A2 = {1.0, 1.9, 3.1, 4.7, 5.4, 4.7, 6.6, 6.7, 9.1, 8.4};

        int[] classes = {2,2,2,2,2,1,1,1,1,1};
        
        KnnAlgorithm knn = new KnnAlgorithm(A1, A2, classes, 3);

        knn.perform();
    }
}
