﻿using System;
using System.ServiceModel;
using Hadouken.Framework.Rpc.Hosting;

namespace Hadouken.Framework.Rpc
{
    public class WcfNamedPipeClientTransport :IClientTransport
    {
        private readonly Uri _rpcHost;
        private readonly Lazy<IWcfRpcService> _rpcProxy;
 
        public WcfNamedPipeClientTransport(string rpcHost): this(new Uri(rpcHost)) {}

        public WcfNamedPipeClientTransport(Uri rpcHost)
        {
            _rpcHost = rpcHost;
            _rpcProxy = new Lazy<IWcfRpcService>(BuildProxy);
        }

        private IWcfRpcService BuildProxy()
        {
            var binding = new NetNamedPipeBinding
            {
                MaxBufferPoolSize = 10485760,
                MaxBufferSize = 10485760,
                MaxConnections = 10,
                MaxReceivedMessageSize = 10485760
            };

            // Create proxy
            var factory = new ChannelFactory<IWcfRpcService>(binding, _rpcHost.ToString());
            return factory.CreateChannel();
        }

        public string Send(string data)
        {
            return _rpcProxy.Value.Call(data);
        }
    }
}
