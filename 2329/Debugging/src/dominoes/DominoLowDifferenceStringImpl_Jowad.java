package dominoes;

import java.util.List;

public class DominoLowDifferenceStringImpl_Jowad implements Domino_Jowad {
    private final String lowDifferenceString;
    private static final char LOW_DIFFERENCE_DELIMITER = '*';

    public DominoLowDifferenceStringImpl_Jowad(int lowPlus8TimesHigh) {
        int high = lowPlus8TimesHigh / 8;
        int low = lowPlus8TimesHigh % 8;
        validatePipCounts(high, low);
        this.lowDifferenceString = low + String.valueOf(LOW_DIFFERENCE_DELIMITER) + (high - low);
    }

    public DominoLowDifferenceStringImpl_Jowad(List<Integer> highSum) {
        if (highSum.size() < 2) {
            throw new IllegalArgumentException("List must have at least two elements");
        }
        int high = highSum.get(0);
        int low = highSum.get(1) - high;
        validatePipCounts(high, low);
        this.lowDifferenceString = low + String.valueOf(LOW_DIFFERENCE_DELIMITER) + (high - low);
    }

    @Override
    public int getHighPipCount() {
        String[] parts = lowDifferenceString.split("\\" + LOW_DIFFERENCE_DELIMITER);
        int low = Integer.parseInt(parts[0]);
        int difference = Integer.parseInt(parts[1]);
        return low + difference;
    }

    @Override
    public int getLowPipCount() {
        String[] parts = lowDifferenceString.split("\\" + LOW_DIFFERENCE_DELIMITER);
        return Integer.parseInt(parts[0]);
    }

    private void validatePipCounts(int high, int low) {
        if (high < MINIMUM_PIP_COUNT || high > MAXIMUM_PIP_COUNT ||
                low < MINIMUM_PIP_COUNT || low > MAXIMUM_PIP_COUNT) {
            throw new IllegalArgumentException("Invalid pip counts.");
        }
    }
}
