import QtQuick 2.0
import AudioAnalysis.Charts 1.0

Item {
	id: root
	Spectrum {
		id: spectrum
		height: root.height
		width: root.width
		backgroundColor: Qt.rgba(0, 255, 255, 255)
		dynamicAxisColor: Qt.rgba(255, 0, 0, 255)
		lineColor: Qt.rgba(0, 0, 0, 255)
		minHz: 10
		maxHz: 25000
		minDB: -120
		maxDB: 0
		deviceType: Spectrum.Device
		updateInterval: 1000
	}

	Component.onCompleted: {


		//spectrum.Start()
	}
}
