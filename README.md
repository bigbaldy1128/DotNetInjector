## DotNetInject
DotNetInject是一个用于.net程序dll注入和hook的类库，支持x86和x64以及.net framework 1.1以上的所有版本
##快速示例
1.定义一个监视器，编译成dll，放入目标程序所在目录下的monitors目录
```
public class CustomMonitor : IMethodMonitor //自定义一个类并继承IMethodMonitor接口
{
    [Monitor("Target","TargetClass","Target.exe")] //目标方法的名称空间，类名，程序集（如果是mscorlib中的可以省略）
    public string Get() //方法的签名要与目标函数一致
    {
        return "B" + Ori();
    }

    [MethodImpl(MethodImplOptions.NoInlining)]
    [Original] //原函数标记
    public string Ori() //方法的签名要与目标函数一致
    {
        return null; //这里写什么无所谓，能编译过即可
    }
}
```
2.注入目标进程并安装监视器。调用Inject.dll中的Inject方法`Inject(target_process_id)`
