
package dominoes;

import java.util.Set;

public class DominoHighLowImpl_Jowad implements Domino {

    private final int highPipCount;
    private final int lowPipCount;

    public static final char HIGH_LOW_STRING_SEPARATOR = DominoRepresentationConstants_Jowad.HIGH_LOW_STRING_SEPARATOR;
    public static final int INDEX_OF_SUM = 0;
    public static final int INDEX_OF_DIFFERENCE = 1;

    public DominoHighLowImpl_Jowad(int highPipCount, int lowPipCount) {
        validatePip(highPipCount);
        validatePip(lowPipCount);
        this.highPipCount = Math.max(highPipCount, lowPipCount);
        this.lowPipCount = Math.min(highPipCount, lowPipCount);
    }

    public static boolean isHighLowString(String str) {
        if (str == null || !str.contains(String.valueOf(HIGH_LOW_STRING_SEPARATOR))) return false;
        String[] parts = str.split(String.valueOf(HIGH_LOW_STRING_SEPARATOR));
        if (parts.length != 2) return false;
        try {
            int high = Integer.parseInt(parts[0]);
            int low = Integer.parseInt(parts[1]);
            return isValidPip(high) && isValidPip(low);
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public DominoHighLowImpl_Jowad(String highLowString) {
        if (!isHighLowString(highLowString))
            throw new IllegalArgumentException("Invalid high:low string: " + highLowString);
        String[] parts = highLowString.split(String.valueOf(HIGH_LOW_STRING_SEPARATOR));
        int high = Integer.parseInt(parts[0]);
        int low = Integer.parseInt(parts[1]);
        this.highPipCount = Math.max(high, low);
        this.lowPipCount = Math.min(high, low);
    }

    public DominoHighLowImpl_Jowad(int[] sumDifference) {
        if (sumDifference == null || sumDifference.length != 2)
            throw new IllegalArgumentException("Array must have exactly two elements");
        int sum = sumDifference[INDEX_OF_SUM];
        int diff = sumDifference[INDEX_OF_DIFFERENCE];
        int high = (sum + diff) / 2;
        int low = (sum - diff) / 2;
        validatePip(high);
        validatePip(low);
        this.highPipCount = high;
        this.lowPipCount = low;
    }

    public DominoHighLowImpl_Jowad(Set<Integer> highLowSet) {
        if (highLowSet == null || highLowSet.size() < 1 || highLowSet.size() > 2)
            throw new IllegalArgumentException("Set must contain 1 or 2 non-null integers");

        Integer[] values = highLowSet.toArray(new Integer[0]);
        for (Integer val : values) validatePip(val);

        if (values.length == 1) {
            this.highPipCount = values[0];
            this.lowPipCount = values[0];
        } else {
            this.highPipCount = Math.max(values[0], values[1]);
            this.lowPipCount = Math.min(values[0], values[1]);
        }
    }

    @Override
    public int getHighPipCount() {
        return highPipCount;
    }

    @Override
    public int getLowPipCount() {
        return lowPipCount;
    }

    private static void validatePip(int pip) {
        if (!isValidPip(pip))
            throw new IllegalArgumentException("Pip out of bounds: " + pip);
    }

    private static boolean isValidPip(int pip) {
        return pip >= MINIMUM_PIP_COUNT && pip <= MAXIMUM_PIP_COUNT;
    }
}
