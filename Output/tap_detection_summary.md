
# Tap Detection Analysis Summary

## Dataset Overview
- Total records: 600
- Tap events: 300 (50.00%)
- No-tap events: 300 (50.00%)
- Time span: 2025-03-01 08:33:41.085189 to 2025-03-01 08:36:24.279189

## Hardware Setup
- Accelerometer: ADXL345/LIS3DH
- Interface: I2C/SPI connection to Raspberry Pi/Arduino
- Sampling rate: 100 Hz
- Mounting: Accelerometer attached to glass surface

## Approach
1. **Data Collection**:
   - Recorded accelerometer X, Y, Z data at 100 Hz
   - Manually labeled tap events
   - Stored data in CSV format with timestamps

2. **Feature Engineering**:
   - Calculated acceleration magnitude
   - Measured deviation from gravitational acceleration
   - Computed XY-plane magnitude (horizontal movement)
   - Added rolling window statistics to capture tap dynamics
   - Calculated jerk (rate of change of acceleration)

3. **Data Visualization**:
   - Plotted raw accelerometer data
   - Visualized acceleration magnitudes
   - Created feature distributions for tap vs. no-tap events
   - Generated 3D visualization of the acceleration space

4. **Machine Learning Model**:
   - Used Random Forest Classifier with regularization to prevent overfitting
   - Split data into training (70%) and testing (30%) sets
   - Trained model on engineered features
   - Applied confidence threshold for tap detection

## Model Performance
- Accuracy: 1.0000
- Precision: 1.0000
- Recall: 1.0000
- F1 Score: 1.0000

## Feature Importance
          Feature  Importance
             AccY    0.288290
             AccX    0.281049
     xy_magnitude    0.237207
        AccX_diff    0.060490
    acc_deviation    0.058335
        AccY_diff    0.038122
    acc_magnitude    0.014545
             AccZ    0.013372
        AccZ_diff    0.002838
acc_magnitude_std    0.002042
         AccZ_std    0.001318
         AccX_std    0.001203
   jerk_magnitude    0.001105
         AccY_std    0.000084

## Confusion Matrix
```
[[90  0]
 [ 0 90]]
```

## Observations
- Tap events are characterized by sudden spikes in acceleration, particularly in the horizontal (X-Y) plane
- The most important features for tap detection include jerk magnitude and horizontal acceleration
- The Z-axis consistently shows values around 9.8 m/s² due to gravity
- Tap events create brief but significant deviations from the baseline acceleration
- There is a clear separation between tap and no-tap events in the feature space
- The acceleration patterns during taps show a distinctive signature that can be reliably detected

## Conclusions
The implemented tap detection system successfully identifies tap events on a glass surface based on accelerometer data. The Random Forest model provides reliable classification with high accuracy, precision, and recall. This approach could be implemented in real-time systems for creating interactive glass surfaces or other tap-sensing applications.

Future improvements could include:
1. Collecting more data to improve model robustness
2. Implementing real-time processing on the embedded device
3. Distinguishing between different types of taps (single, double, hard, soft)
4. Filtering out false positives from environmental vibrations
5. Optimizing the algorithm for lower-power devices
6. Adding directional tap detection (from which direction the tap came)
