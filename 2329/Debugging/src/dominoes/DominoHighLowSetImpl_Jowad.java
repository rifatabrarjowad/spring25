package dominoes;

import java.util.Set;

public class DominoHighLowSetImpl_Jowad implements Domino {

    private final int highPipCount;
    private final int lowPipCount;

    public static final char SUM_DIFFERENCE_DELIMITER = DominoRepresentationConstants_Jowad.SUM_DIFFERENCE_DELIMITER;

    public DominoHighLowSetImpl_Jowad(int highPipCount, int lowPipCount) {
        validatePip(highPipCount);
        validatePip(lowPipCount);
        this.highPipCount = Math.max(highPipCount, lowPipCount);
        this.lowPipCount = Math.min(highPipCount, lowPipCount);
    }

    public static boolean isSumDifferenceString(String str) {
        if (str == null || !str.contains(String.valueOf(SUM_DIFFERENCE_DELIMITER))) return false;
        String[] parts = str.split(String.valueOf(SUM_DIFFERENCE_DELIMITER));
        if (parts.length != 2) return false;
        try {
            int sum = Integer.parseInt(parts[0]);
            int diff = Integer.parseInt(parts[1]);
            int high = (sum + diff) / 2;
            int low = (sum - diff) / 2;
            return isValidPip(high) && isValidPip(low);
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public DominoHighLowSetImpl_Jowad(String sumDifferenceString) {
        if (!isSumDifferenceString(sumDifferenceString))
            throw new IllegalArgumentException("Invalid sum,difference string: " + sumDifferenceString);
        String[] parts = sumDifferenceString.split(String.valueOf(SUM_DIFFERENCE_DELIMITER));
        int sum = Integer.parseInt(parts[0]);
        int diff = Integer.parseInt(parts[1]);
        int high = (sum + diff) / 2;
        int low = (sum - diff) / 2;
        validatePip(high);
        validatePip(low);
        this.highPipCount = high;
        this.lowPipCount = low;
    }

    public static boolean isLowPlus8TimesHighInteger(int k) {
        int high = k / 8;
        int low = k % 8;
        return isValidPip(high) && isValidPip(low);
    }

    public DominoHighLowSetImpl_Jowad(int lowPlus8TimesHigh) {
        int high = lowPlus8TimesHigh / 8;
        int low = lowPlus8TimesHigh % 8;
        validatePip(high);
        validatePip(low);
        this.highPipCount = Math.max(high, low);
        this.lowPipCount = Math.min(high, low);
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
