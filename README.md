
## BLE Heart Rate Demo - Practical Test

### Objective
Implement a Qt QML-based BLE Central application that scans for BLE peripherals, connects, and displays real-time heart rate data in a chart. This test assesses your skills in C++, Qt QML, BLE, unit testing, and CI/CD workflows.

### Instructions
1. **Environment Setup**
	- Download and install the open source version of Qt Creator.
 		- Windows
    		- Make sure you have [Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x64.exe) for Visual Studio 2019 installed. You might already have it, as it's a very common dependency.

	- Install the nRF Connect app on your mobile device to simulate a BLE peripheral (Macro instructions provided separately).
	- Clone this public VitalTrace repository.
2. **Implementation**
	- Build a simple BLE Central app using Qt QML that:
	  - Scans for BLE peripherals
	  - Connects to a device
	  - Subscribes to heart rate notifications
	  - Displays heart rate points in real time on a chart using QML components
3. **Testing**
	- Add at least one unit test using googletest.
	- Ensure tests are detected and reported by SonarCloud.
4. **CI/CD & SonarCloud**
	- The repository is integrated with GitHub Actions and SonarCloud.
	- The build and run tests steps should be implemented. The steps are marked with TODO placeholder
	- Your PR will trigger the CI/CD pipeline and code analysis.
5. **Submission**
	- Submit your solution as a Pull Request (PR) to this repository.
	- The PR will be reviewed for code quality, test coverage, and ability to resolve issues.

### Project Structure

```
ble-heart-rate-demo/
├── .github/
│   └── workflows/
│       └── ci.yml            # GitHub Actions CI pipeline
├── sonar-project.properties  # SonarCloud configuration
├── CMakeLists.txt            # Qt project build config
├── app/
│   ├── main.cpp              # Application entry point with QML engine
│   ├── qml/
│   │   └── Main.qml          # Main QML interface
│   └── CMakeLists.txt        # App build configuration
|__ docs
|	|__ nRF Connect
├── test/
│   ├── main.cpp              # Test runner
│   ├── tst_sample.cpp        # Example googletest unit test
│   └── CMakeLists.txt        # Test build configuration
├── libs/
│   └── googletest/           # Google Test framework
├── utils/
│   └── nrfconnect-notify-heart-rate-macro.xml  # nRF Connect macro
└── README.md
```
### Nordic's nRF Connect Setup

Nordic's nRF Connect mobile app can be used to simulate a BLE peripheral. You can find this app on Android Play Store.

The following instructions were tested on an Android device.

- Download these two XML files on your device:
    - [vitaltrace-ble-test.xml](docs/nRF%20Connect/vitaltrace-ble-test.xml)
    - [notify-heart-rate.xml](docs/nRF%20Connect/notify-heart-rate.xml)

- In the app, click the hamburger button to open the navigation drawer on the left side of the screen, then click `Configure GATT server`.
- Select `Sample configuration` which includes the Heart Rate service.
- Press the back button to go back to the `Devices` screen.
- Open the `Advertiser` tab and add a new advertiser by clicking the floating action button in the bottom right corner. You'll need to provide a display name for it and check the `Connectable` option.
- Add a record of type "Complete Local Name" to make the device discoverable with a recognizable name.
- Enable the advertiser, if it's not enabled already, by activating the switch.
- Open the application on your computer and click the `Scan` button. You should see your phone among the scanned peripherals after a few seconds.
    - The name that will appear in the list is _not_ the display name you just chose for the advertiser.
    - You can choose the actual name by clicking the pencil icon that's in the toolbar at the top of the screen, just next to the screen title (`Devices`).

- Once you see your phone among the scanned peripherals, click the `Stop` button, then `Connect`.

- When the peripheral is connected, the application should be able to find the Heart Rate service.
    - The app will try to enable notifications for the Heart Rate Measurement characteristic.
    - No values will be automatically sent yet, we need to configure a macro first.

- Click the floating action button in the bottom right corner to open the `Macros` panel at the bottom of the screen.
- Import the `notify-heart-rate.xml` file you downloaded earlier.
    - Note: There's no button to delete macros, but if needed you can do it by swiping them.

- Open the `Notify heart rate` macro, check the loop button, then execute it by clicking the play button.
    - You should now receive heart rate values periodically.
