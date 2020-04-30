const texture = new THREE.TextureLoader().load("assets/img/texturabalon.jpg")
const light = new THREE.DirectionalLight(0xffffff, 1)
light.position.set(-20, 20, 20)

var scene = new THREE.Scene()
var aspect = window.innerWidth / window.innerHeight
var camera = new THREE.PerspectiveCamera(75, aspect, 0.1, 1000)
var renderer = new THREE.WebGLRenderer()
renderer.setSize(window.innerWidth, window.innerHeight)
document.body.appendChild(renderer.domElement)

scene.add(light)

var geometry = new THREE.BoxGeometry(1, 1, 1)
var material = new THREE.MeshNormalMaterial()
var cube = new THREE.Mesh(geometry, material)
scene.add(cube)
camera.position.z = 5
controls = new THREE.OrbitControls(camera, renderer.domElement)

var loader = new THREE.ObjectLoader()

loader.load("../json/bola1.json", function(group) {
    mesh = group.children[0]
    mesh.material = new THREE.MeshPhongMaterial({
        map: texture
    })
    mesh.position.x = 5
    scene.add(mesh)
})


var render = function() {
    requestAnimationFrame(render)
    cube.rotation.x += 0.1
    cube.rotation.y += 0.1
    renderer.render(scene, camera)
}

render()