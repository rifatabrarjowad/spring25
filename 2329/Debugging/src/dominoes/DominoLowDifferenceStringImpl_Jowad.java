// Updated DominoLowDifferenceStringImpl_Jowad.java
package dominoes;

import java.util.List;

public class DominoLowDifferenceStringImpl_Jowad implements Domino {

    private final int highPipCount;
    private final int lowPipCount;
    private static final char LOW_DIFFERENCE_DELIMITER = DominoRepresentationConstants_Jowad.LOW_DIFFERENCE_DELIMITER;

    public DominoLowDifferenceStringImpl_Jowad(int lowPlus8TimesHigh) {
        int high = lowPlus8TimesHigh / 8;
        int low = lowPlus8TimesHigh % 8;
        validatePip(high);
        validatePip(low);
        this.highPipCount = Math.max(high, low);
        this.lowPipCount = Math.min(high, low);
    }

    public DominoLowDifferenceStringImpl_Jowad(List<Integer> highSum) {
        if (highSum == null || highSum.size() != 2)
            throw new IllegalArgumentException("List must have exactly 2 integers");

        int high = highSum.get(0);
        int sum = highSum.get(1);
        int low = sum - high;
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
