## DotNetInjector
DotNetInjector是一个用于.net程序dll注入和方法hook的类库
##特点
* 支持32bit和64bit的.net程序
* 支持.net framework 2.0以上的所有版本
* 支持静态方法，实例方法和属性的hook
* 支持.net基础类库方法的hook
* 无任何性能影响

##Hook方法示例
1.定义一个监视器，编译成dll，放入程序所在目录下的monitors目录
```
public class CustomMonitor : IMethodMonitor //自定义一个类并继承IMethodMonitor接口
{
    [Monitor("Target","TargetClass","Target.exe")] //目标方法的名称空间，类名，程序集（如果是mscorlib中的可以省略）
    public string Get() //方法签名要与目标方法一致
    {
        return "B" + Ori();
    }

    [MethodImpl(MethodImplOptions.NoInlining)]
    [Original] //原函数标记
    public string Ori() //方法签名要与目标方法一致
    {
        return null; //这里写什么无所谓，能编译过即可
    }
}
```
2.安装监视器
`Monitor.Install("monitors")` //这里指定默认目录为monitors
##Dll注入示例
示例程序在BinTest_x64目录下，启动target.exe,点击【Call】按钮，弹出"A"，启动MainHook点击【注入】按钮后再点击【Call】按钮，弹出"BA"
