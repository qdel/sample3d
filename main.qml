// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick3D
import Example

Window {
    id: window
    width: 640
    height: 640
    visible: true
    color: "black"

    StreamView {
        id: test
        width: 100
        height: 100
    }

    View3D {
        id: view
        anchors.fill: parent

        PerspectiveCamera {
            position: Qt.vector3d(0, 200, 300)
            eulerRotation.x: -30
        }

        DirectionalLight {
            eulerRotation.x: -30
        }

        Model {
            //! [3dcube]
            id: cube
            source: "#Cube"
            materials: CustomMaterial {
                property TextureInput textureMap: TextureInput {
                    texture: Texture {
                        sourceItem: test
                        magFilter: Texture.Linear
                        minFilter: Texture.Linear
                    }
                }
                fragmentShader: "Plane.frag"
                vertexShader: "Plane.vert"
                cullMode: DefaultMaterial.NoCulling
                depthDrawMode: Material.OpaquePrePassDepthDraw
                shadingMode: CustomMaterial.Shaded
                sourceBlend: CustomMaterial.SrcAlpha
                destinationBlend: CustomMaterial.OneMinusSrcAlpha
            }

            eulerRotation.y: 90
            //! [3dcube]

            Vector3dAnimation on eulerRotation {
                loops: Animation.Infinite
                duration: 5000
                from: Qt.vector3d(0, 0, 0)
                to: Qt.vector3d(360, 0, 360)
            }
        }
    }

}
